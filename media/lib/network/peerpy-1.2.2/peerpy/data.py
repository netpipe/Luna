import json
import pickle

from typing import Any
from dataclasses import dataclass

from .exceptions import DataTypeError


@dataclass
class Data():

    _type: str
    buffer: bytes = b""
    decoded_data: Any = None
    encoded_data: bytes = None

    def get_type(self):
        return self._type

    def encode(self):
        if self.encoded_data is None:
            if self._type == "raw":
                self.encoded_data = pickle.dumps(self.decoded_data)
            elif self._type == "json":
                self.encoded_data = json.dumps({
                    "data": self.decoded_data
                }).encode("utf-8")
            else:
                if not isinstance(self.decoded_data, bytes):
                    raise DataTypeError("data is not a bytes object")

                self.encoded_data = self.decoded_data

        return self.encoded_data

    def decode(self):
        if self.decoded_data is None:
            if self._type == "raw":
                self.decoded_data = pickle.loads(self.buffer)
            elif self._type == "json":
                self.decoded_data = json.loads(self.buffer)["data"]
            else:
                self.decoded_data = self.buffer

        return self.decoded_data

    def __len__(self):
        if self.encoded_data is None:
            return 0

        return len(self.encoded_data)
