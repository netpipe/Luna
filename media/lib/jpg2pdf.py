import imghdr
from contextlib import contextmanager

__version__ = '0.1.0'

PDF_DPI = 72
MONITOR_DPI = 96


class PDFBuilder:
    def __init__(self, pdf_file):
        self.xref = {}
        self.refs = set()
        self.pages = []
        self.num_of_img = 0
        self.file = open(pdf_file, 'wb')

        self._write('%PDF-1.7\n')
        self.catalog = self._bgn_obj()
        self.root = self._reserve_obj()
        self._write(Type='/Catalog', Pages=(self.root, 0))
        self._end_obj()

    def add(self, jpg_file):
        data, width, height, num_col = self._jpg_open(jpg_file)
        page_width = width * PDF_DPI / MONITOR_DPI
        page_height = height * PDF_DPI / MONITOR_DPI

        img_index = self._bgn_obj()
        self._write(
            Type='/XObject',
            Subtype='/Image',
            Filter='/DCTDecode',
            BitsPerComponent='8',
            ColorSpace='/DeviceGray' if num_col == 1 else '/DeviceRGB',
            Width=width,
            Height=height,
            Length=len(data))
        self._write('stream\n')
        self.file.write(data)
        self._write('endstream\n')
        self._end_obj()

        cts_index = self._bgn_obj()
        self._write(Length=(cts_index + 1, 0))
        self._write('stream\n')
        bgn_fp = self.file.tell()
        self._write('q\n1 0 0 1 0.00 0.00 cm\n')
        self._write(f'{page_width:.2f} 0 0 {page_height:.2f} 0 0 cm\n')
        self._write(f'/I{self.num_of_img} Do\nQ\n')
        length = self.file.tell() - bgn_fp
        self._write('endstream\n')
        self._end_obj()

        self._bgn_obj()
        self._write(f'{length}\n')
        self._end_obj()

        rsc_index = self._bgn_obj()
        self._write(ProcSet=f'[/PDF/{"ImageB" if num_col == 1 else "ImageC"}]',
                    XObject={f'I{self.num_of_img}': (img_index, 0)})
        self._end_obj()

        page_index = self._bgn_obj()
        self.pages.append(page_index)
        self._write(Type='/Page',
                    Parent=(self.root, 0),
                    MediaBox=[0, 0, page_width, page_height],
                    Contents=(cts_index, 0),
                    Resources=(rsc_index, 0))
        self._end_obj()

        self.num_of_img += 1

    def close(self):
        self._bgn_obj(reserved=self.root)
        self._write(Type='/Pages',
                    Kids=[(i, 0) for i in self.pages],
                    Count=len(self.pages))
        self._end_obj()

        xref_fp = self.file.tell()
        self._write('xref\n')
        self._write(f'0 {len(self.xref) + 1}\n')
        self._write(f'{0:010} 65535 f\n')
        for r in sorted(self.xref.keys()):
            self._write(f'{self.xref[r]:010} {0:05} n\n')

        self._write('trailer\n')
        self._write(Root=(self.catalog, 0), Size=len(self.xref) + 1)
        self._write(f'startxref\n{xref_fp}\n')
        self._write('%%EOF\n')
        self.file.close()

    def _jpg_open(self, path):
        if imghdr.what(path) != 'jpeg':
            raise Exception('Not a valid JPEG file')

        with open(path, 'rb') as f:
            data = f.read()
            data_len = len(data)

            blk_len = int.from_bytes(data[4:6], 'big')
            index = 4
            while index + blk_len < data_len:
                index += blk_len
                if data[index] != 0xFF:
                    raise Exception('Not a valid JPEG marker')
                if data[index + 1] == 0xC0 or data[index + 1] == 0xC2:
                    width = int.from_bytes(data[index + 7:index + 9], 'big')
                    height = int.from_bytes(data[index + 5:index + 7], 'big')
                    num_of_col = data[index + 9]
                    return data, width, height, num_of_col
                else:
                    index += 2
                    blk_len = int.from_bytes(data[index:index + 2], 'big')
            else:
                raise Exception('Failed to find SOF marker')

    def _write(self, *args, **kwargs):
        def to_str(obj):
            if type(obj) == str:
                return obj
            if type(obj) == tuple:
                return '%i %i R' % obj
            if type(obj) == list:
                strlist = [to_str(element) for element in obj]
                return f'[{" ".join(strlist)}]'
            if type(obj) == dict:
                strlist = [f'/{to_str(k)} {to_str(v)}' for k, v in obj.items()]
                return f'<<\n{" ".join(strlist)} >>\n'
            if type(obj) == int:
                return str(obj)
            if type(obj) == float:
                return f'{obj:.2f}'
            else:
                raise Exception(f'Not supported type: {repr(obj)}')

        obj = None
        if args:
            obj = args[0]
        elif kwargs:
            obj = kwargs

        if obj:
            if type(obj) != bytes:
                obj = to_str(obj).encode('ascii')
            self.file.write(obj)

    def _bgn_obj(self, reserved=None):
        if reserved:
            i = reserved
        else:
            i = len(self.refs) + 1
            self.refs.add(i)
        self.xref[i] = self.file.tell()
        self._write(f'{i} 0 obj\n')
        return i

    def _end_obj(self):
        self._write('endobj\n')

    def _reserve_obj(self):
        i = len(self.refs) + 1
        self.refs.add(i)
        return i


@contextmanager
def create(pdf_file):
    pdf = PDFBuilder(pdf_file)
    try:
        yield pdf
    finally:
        pdf.close()
