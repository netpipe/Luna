import os
import tempfile
import time
import unittest

from qftplib.client import FTPClient


class FTPTest(unittest.TestCase):
    host = os.environ.get('SFTP_HOST_TEST')
    user = os.environ.get('SFTP_USER_TEST')
    password = os.environ.get('SFTP_PASS_TEST')
    dir = os.environ.get('SFTP_DIR_TEST')
    port = 22

    def test_name(self):
        with FTPClient(self.host, self.user, self.password, port=self.port, protocol='sftp')as sftp:
            assert str(sftp) == f'<FTPClient({self.host}, {self.user}, xxxx, port = {self.port}, protocol = sftp)>'

    def test_listdir(self):
        with FTPClient(self.host, self.user, self.password, port=self.port, protocol='sftp')as sftp:
            directory_files = sftp.listdir(self.dir)

            assert len(directory_files) > 0

    def test_pwd_chdir(self):
        with FTPClient(self.host, self.user, self.password, port=self.port, protocol='sftp')as sftp:
            sftp.chdir(self.dir)

            assert sftp.pwd() == f'/home/{self.user}/{self.dir}'

    def test_rmdir_mkdir(self):
        with FTPClient(self.host, self.user, self.password, port=self.port, protocol='sftp')as sftp:
            sftp.chdir(self.dir)
            new_dir = str(int(time.time()))
            sftp.mkdir(new_dir)
            files = sftp.listdir('.')

            assert f'{new_dir}' in files

            sftp.rmdir(f'/home/{self.user}/{self.dir}/{new_dir}')

            files = sftp.listdir('.')

            assert f'{new_dir}' not in files

    def test_rename(self):
        with FTPClient(self.host, self.user, self.password, port=self.port, protocol='sftp')as sftp:
            sftp.chdir(self.dir)
            new_dir = str(int(time.time()))
            sftp.mkdir(new_dir)

            sftp.rename(f'/home/{self.user}/{self.dir}/{new_dir}', f'/home/{self.user}/{self.dir}/{new_dir}_renamed')

            files = sftp.listdir('.')

            assert f'{new_dir}_renamed' in files

            sftp.rmdir(f'/home/{self.user}/{self.dir}/{new_dir}_renamed')

    def test_put_delete(self):
        with FTPClient(self.host, self.user, self.password, port=self.port,
                       protocol='sftp')as sftp, tempfile.NamedTemporaryFile() as f:
            remotepath = os.path.join(self.dir, os.path.basename(f.name))
            sftp.put(f.name, remotepath)

            sftp.delete(remotepath)

            files = sftp.listdir(self.dir)

            assert remotepath not in files

    def test_get(self):
        with FTPClient(self.host, self.user, self.password, port=self.port,
                       protocol='sftp')as sftp, tempfile.NamedTemporaryFile(mode='w') as f:
            files = sftp.listdir(self.dir)

            filename = next((f for f in files if f.endswith('.csv') or f.endswith('.txt')), None)

            sftp.get(f'/home/{self.user}/{self.dir}/{filename}', f.name)

            assert os.path.exists(f.name)
            assert os.path.isfile(f.name)
