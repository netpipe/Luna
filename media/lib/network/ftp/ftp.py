import os
import sys
import glob
import ftplib
import traceback

class FTP(object):

    status = False

    """docstring for FTP"""
    def __init__(self, server, account, password):
        try:
            self.login(server, account, password)
            self.set_dir()
            self.account = account
        except:
            self.status = False
            t, v, tb = sys.exc_info()
            raise Exception(traceback.format_exception(t,v,tb)[-1])

    def login(self, ftp_server, account, password):
        self.ftp = ftplib.FTP(ftp_server)
        self.ftp.set_pasv("ture")
        self.ftp.login(account, password)
        self.status = True

    def set_dir(self):
        self.dir_list = self.ftp.nlst()
        self.dir_list.remove('.')
        self.dir_list.remove('..')
        self.dir_list.sort()

    def upload(self, file_name):
        if os.path.exists(file_name):
            if os.path.isdir(file_name):
                os.chdir(file_name)
                self.mkdir(file_name)
                self.cd(file_name)
                for i in glob.glob('*'):
                    self.upload(i)
                self.cd('..')
                os.chdir('..')
            else:
                fp = open(file_name, "rb")
                self.ftp.storbinary("STOR {}".format(file_name), fp)
                fp.close()
                self.set_dir()
                print('upload: [Success] {}'.format(self.current() + file_name))
        else:
            print('upload: [Error] {}'.format(file_name))

    def download(self, file_name):
        if file_name in self.dir_list:
            try:
                self.ftp.retrbinary('RETR {}'.format(file_name), open(file_name, 'wb').write)
                print('download: [Success] {}'.format(self.current() + file_name))
            except:
                try:
                    os.remove(file_name)
                    os.mkdir(file_name)
                except:
                    pass
                pwd = self.current()
                self.cd(file_name)
                os.chdir(file_name)
                for i in self.dir_list:
                    self.download(i)
                self.cd(pwd)
                os.chdir('../')
        else:
            print('download: [Error] {}'.format(self.current() + file_name))

    def current(self):
        path = self.ftp.pwd()
        return path if path == '/' else path + '/'

    def pwd(self):
        print(self.ftp.pwd())

    def cd(self, dir_name):
        try:
            self.ftp.cwd(dir_name)
            self.set_dir()
        except:
            print('cd: [Error] {}'.format(self.current() + dir_name))

    def mkdir(self, dir_name):
        if not dir_name in self.dir_list:
            self.ftp.mkd(dir_name)
            self.set_dir()
        else:
            print('mkdir: [Error] {}'.format(self.current() + dir_name))

    def rm(self, file_name):
        if file_name in self.dir_list:
            try:
                self.ftp.delete(file_name)
                print('rm <file>: [Success] {}'.format(self.current() + file_name))
            except:
                self.cd(file_name)
                for i in self.dir_list:
                    self.rm(i)
                self.cd('..')
                self.ftp.rmd(file_name)
                print('rm <dir>: [Success] {}'.format(self.current() + file_name))
            self.set_dir()
        else:
            print('rm: [Error] {}'.format(self.current() + file_name))

    def all_download(self, pass_list=[]):
        os.makedirs(self.account, exist_ok=True)
        os.chdir(self.account)
        dl_list = self.dir_list
        for i in dl_list:
            if not i in pass_list and not self.account in i:
                self.download(i)

    def ls(self):
        print(self.dir_list)

    def cmd(self, cmd_txt):
        return self.ftp.sendcmd(cmd_txt)
