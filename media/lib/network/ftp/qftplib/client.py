import os
from ftplib import FTP

import paramiko

from qftplib.exceptions import InvalidConnection


class FTPClient:
    def __init__(self, host, user, password, port=21, protocol='ftp'):
        assert protocol.strip().lower() in ['ftp', 'sftp'], 'Invalid protocol, options are: SFTP, FTP'
        self.host = host
        self.user = user
        self.password = password
        self.port = port
        self.protocol = protocol.strip().lower()

        self._transport = None
        self._conn = None

    def __enter__(self):
        self._start_connection()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self._close_connection()

    def __repr__(self):
        return f'<FTPClient({self.host}, {self.user}, xxxx, port = {self.port}, protocol = {self.protocol})>'

    def _start_connection(self):
        func = {
            'ftp': self._start_ftp_connection,
            'sftp': self._start_sftp_connection
        }[self.protocol]

        try:
            func()
        except:
            raise InvalidConnection(f'Error connecting to {self.protocol.upper()} server')

    def _close_connection(self):
        if self._transport is not None:
            self._transport.close()

        if self._conn is not None:
            self._conn.close()

    def _start_ftp_connection(self):
        self._conn = FTP()
        self._conn.connect(self.host, self.port)
        self._conn.login(self.user, self.password)

    def _start_sftp_connection(self):
        self._transport = paramiko.Transport((self.host, self.port))
        self._transport.connect(None, self.user, self.password)
        self._conn = paramiko.SFTPClient.from_transport(self._transport)

    def listdir(self, path):
        return self._conn.listdir(path) if self.protocol == 'sftp' else self._conn.nlst(path)

    def chdir(self, path):
        self._conn.chdir(path) if self.protocol == 'sftp' else self._conn.cwd(path)

        return True

    def mkdir(self, path):
        self._conn.mkdir(path) if self.protocol == 'sftp' else self._conn.mkd(path)

        return True

    def rmdir(self, path):
        self._conn.rmdir(path) if self.protocol == 'sftp' else self._conn.rmd(path)

        return True

    def pwd(self):
        return self._conn.getcwd() if self.protocol == 'sftp' else self._conn.pwd()

    def rename(self, oldpath, newpath):
        self._conn.rename(oldpath, newpath)

        return True

    def delete(self, path):
        self._conn.remove(path) if self.protocol == 'sftp' else self._conn.delete(path)

        return True

    def get(self, remotepath, localpath, callback=None):
        if callback is not None:
            assert callable(callback), "Callback must to be a function"

        path = os.path.split(localpath)[0]

        if not os.path.exists(path):
            os.mkdir(path)

        if self.protocol == 'sftp':
            self._conn.get(remotepath, localpath, callback=callback)
        else:
            with open(localpath, 'wb') as f:
                self._conn.retrbinary(f'RETR {remotepath}', f.write)

            if callback is not None:
                callback()

    def put(self, localpath, remotepath, callback=None):
        if callback is not None:
            assert callable(callback), "Callback must to be a function"

        if not os.path.exists(localpath):
            raise Exception(f'{localpath} does not exists')

        if self.protocol == 'sftp':
            self._conn.put(localpath, remotepath, callback=callback)
        else:
            with open(localpath, 'rb') as f:
                self._conn.storbinary(f'STOR {remotepath}', f)

            if callback is not None:
                callback()
