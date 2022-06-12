import time 
import os
import re
from pythonFTP.ftplib2 import FTP 
import traceback

# Copyright AsajuHuishi 20/12/29

class FTPTools:
    def __init__(self, ip, username, password, port=21, bufsize=1024):
        super(FTPTools, self).__init__()
        self.ftp = FTP() 
        self.ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息 
        self.ftp.connect(ip, port)#连接 ftp21端口
        self.ftp.login(username, password)#登录，如果匿名登录则用空串代替即可 
        # print(ftp.getwelcome())#显示ftp服务器欢迎信息 
        self.bufsize = bufsize#设置缓冲块大小 
        self.ftp.set_debuglevel(0) 
        self.ftp.encoding = "utf-8"

    def run(self, ftp=None, local=None, status=None):   
        if status == 'upload folder': # 上传文件夹
            assert local != None and ftp != None, 'Upload folder: Local folder or FTP folder is not specified'
            self.uploadFolder(local, ftp)
            self.shutdown()
        elif status == 'upload file': # 上传文件
            assert local != None and ftp != None, 'Upload file: Local file or FTP folder is not specified'
            self.uploadFile(local, ftp)      
            self.shutdown()
        elif status == 'download folder': # 下载文件夹
            assert local != None and ftp != None, 'Download folder: Local folder or FTP folder is not specified'
            self.downloadFolder(local, ftp)
            self.shutdown()
        elif status == 'download file': # 下载文件夹
            assert local != None and ftp != None, 'Download file: Local file or FTP folder is not specified'
            self.downloadFile(local, ftp)
            self.shutdown()
        elif status == 'delete folder': # 删除文件夹
            assert ftp != None, 'Delete folder: FTP file is not specified'
            self.deleteFolder(ftp)
        elif status == 'delete file': # 删除文件
            assert ftp != None, 'Delete file: FTP file is not specified'
            self.deleteFile(ftp)
        elif status == 'create folder': # 新建文件夹
            assert ftp != None, 'Delete file: FTP file is not specified'
            self.createFolderFTP(ftp)
        else:
            raise NameError("Status does not have this parameter")
        
        
    def shutdown(self):
        self.file_handler.close() 
        self.ftp.quit() 

    def getSubContent(self): # 找到该路径下一级的所有文件和文件夹（用于递归删除）
        subContent = (re.findall('\d+?:\d+? (.*?) [-|r|w|d]' ,self.ftp.dirs())+[self.ftp.dirs().split(' ')[-1]]) # 记录要删除的路径下所有文件和目录
        while len(subContent) and subContent[0].startswith('.'):
            subContent.pop(0)
        return subContent
        
    def createFolderFTP(self, ftpPath):
        ftpPath = ftpPath.rstrip('/') 
        # 判断目标文件夹是否存在，如果不存在就创建
        self.ftp.cwd('/') # 每次从根目录开始判断防止出错
        try:
            self.ftp.cwd(ftpPath)
        except Exception as r:
            print('The FTP server does not have this directory: {}'.format(ftpPath))    
            # 在ftp服务器端递归建立目录
            for splitPath in ftpPath.strip('/').split('/'):
                curDir = self.ftp.dirs()  # 查找当前ftp服务器路径下包含的文件夹
                # print('curDirHasFolder',curDir.split())
                if splitPath in curDir.split(): # 判断该路径是否存在
                    print(splitPath+' exists')
                    self.ftp.cwd(splitPath)   # 转到当前路径
                else:
                    print(splitPath+' doesnot exist, create path...')
                    self.ftp.mkd(splitPath)   # 新建路径
                    self.ftp.cwd(splitPath)   # 转到当前路径        
            assert self.ftp.pwd() == ftpPath, 'Check that the FTP directory has been created correctly!'
        print('Create folder {} OK.'.format(ftpPath))
            
    def uploadFolder(self, localPath, ftpPath): # 上传文件夹
        self.createFolderFTP(ftpPath)
        # 在本地文件夹下文件上传至ftp服务器,保持文件名一致
        try:
            print('Start uploading folder {}...'.format(localPath))
            if not localPath.endswith('/'):
                localPath += '/' 
            print(localPath)
            self.ftp.set_debuglevel(0) 
            for file in os.listdir(localPath):
                if os.path.isdir(localPath+file): # 文件夹里面的文件夹
                    self.uploadFolder(localPath+file, ftpPath+file) # 递归
                else:
                    self.file_handler = open(localPath+file,'rb')#以读模式在本地打开文件 
                    self.ftp.storbinary('STOR '+file, self.file_handler, self.bufsize) #上传文件                
                    assert self.ftp.size(file) == os.path.getsize(localPath+file), 'The uploaded file size is inconsistent with the local file size.'
                    print("FTP upload file {} OK".format(file))  
                self.ftp.cwd(ftpPath) # 返回当前ftp目录 否则会继续在当前目录下操作
        except Exception as r:
            print(traceback.format_exc())
            raise RuntimeError('The FTP server failed to upload the file {}'.format(ftpPath))            
        else:
            print('Upload folder {} OK'.format(localPath)) 
            
    def uploadFile(self, localFile, ftpPath):
        self.createFolderFTP(ftpPath)
        # 本地文件上传至ftp服务器,保持文件名一致
        dir, file = os.path.split(localFile)
        try:
            print('Start uploading file...')
            print(file)
            self.file_handler = open(localFile,'rb')#以读模式在本地打开文件 
            self.ftp.storbinary('STOR '+file, self.file_handler, self.bufsize) #上传文件 
            self.ftp.set_debuglevel(0) 
            assert self.ftp.size(file) == os.path.getsize(localFile), 'The uploaded file size is inconsistent with the local file size.'           
        except Exception as r:
            print(traceback.format_exc())
            raise RuntimeError('The FTP server failed to upload the file {}'.format(ftpPath)) 
        else:
            print("FTP upload file{} OK".format(file))     
    
    def deleteFile(self, ftpFile):
        # 将文件路径分为两部分
        dir, file = os.path.split(ftpFile)
        try:
            self.ftp.cwd(dir)
        except Exception as r:
            print('The FTP server does not have this directory.') 
        try:
            self.ftp.delete(file)
        except Exception as r:
            print('Unable to delete: the file {} does not exist.'.format(file)) 
        else: 
            print('FTP delete file {} OK'.format(file))
        
    def deleteFolder(self, ftpPath):       # 递归删除该文件夹下所有内容，并删除该文件夹本身 
        self.ftp.cwd('/')
        if not ftpPath.endswith('/'):
            ftpPath += '/' 
        try:
            self.ftp.cwd(ftpPath)
        except Exception as r:
            print('The FTP server does not have this directory') 
        subContent = self.getSubContent()  # 获得目录中下一层级所有文件和文件夹
        # print('a', subContent)
        # print('b', self.ftp.dirs())
        if len(subContent) != 0: # 当前目录如果不为空，删除所有文件，并递归进入下级目录进入删除
            self.ftp.cwd(ftpPath)
            # 删除所有文件
            subFileLst = self.ftp.nlst()
            for file in subFileLst:
                self.deleteFile(file)
            # 递归进入下级目录
            for folder in list(set(subContent)-set(subFileLst)):
                self.deleteFolder(ftpPath+folder)
        subContent2 = self.getSubContent() # 再次获得目录中下一层级所有文件和文件夹
        assert len(subContent2) == 0, 'There is still content in the current directory!'
        # 目前当前目录为空 则可以直接删除该文件夹本身 
        try:
            baseDir, curFolder = os.path.split(ftpPath.rstrip('/')) # 将文件路径分为两部分
            self.ftp.cwd(baseDir) # 退到上一目录删除该文件夹
            self.ftp.rmd(curFolder)
        except Exception as r:
            print(traceback.format_exc())
            print('Unable to delete: folder {}'.format(curFolder))             
        else:
            print('Delete folder {} OK'.format(curFolder))   
            
    def downloadFile(self, localPath, ftpFile):
        # 将文件路径分为两部分
        dir, file = os.path.split(ftpFile)
        try:
            self.ftp.cwd(dir)
        except Exception as r:
            print('The FTP server does not have this directory {}'.format(dir))          
        if not localPath.endswith('/'):
            localPath += '/' 
        try:
            print('Start downloading files...')            
            self.file_handler = open(localPath+file,'wb')#以写模式在本地打开文件 
            self.ftp.set_debuglevel(0) 
            self.ftp.retrbinary("RETR "+file, self.file_handler.write, self.bufsize)  #下载FTP文件
            print("FTP download file{} OK".format(file)) 
        except Exception as r:
            print(traceback.format_exc())
            raise RuntimeError('The FTP server failed to download the file {}'.format(ftpFile)) 
        else:
            print('FTP upload file {} OK'.format(ftpFile))

    def downloadFolder(self, localPath, ftpPath):
        self.ftp.cwd('/')
        os.system("cd /")
        if not ftpPath.endswith('/'):
            ftpPath += '/' 
        if not localPath.endswith('/'):
            localPath += '/' 
        try:
            self.ftp.cwd(ftpPath)
        except Exception as r:
            print('The FTP server does not have this directory {}'.format(ftpPath))          
        # 如果目录为空，提醒
        subContent = self.getSubContent()
        if  len(subContent)== 0:        
            print('Note: The FTP directory {} is empty.'.format(self.ftp.pwd()))
        # 本地路径如果不存在就创建
        if not os.path.isdir(localPath):
            try:
                os.system('mkdir -p {}'.format(localPath))
            except OSError as r:
                print('Failed to create {}'.format(localPath),r)
            else:
                os.system('cd {}'.format(localPath))       
        # 下载所有文件，并进入文件夹递归下载            
        try:
            print('Start downloading file...')    
            # 找到文件
            subFileLst = self.ftp.nlst()            
            self.ftp.set_debuglevel(0) 
            for file in subFileLst:
                self.file_handler = open(localPath+file,'wb')#以写模式在本地打开文件 
                self.ftp.retrbinary("RETR "+file, self.file_handler.write, self.bufsize)  #下载FTP文件
                print("FTP download file {} OK".format(file)) 
            # 递归进入下级目录
            for folder in list(set(subContent)-set(subFileLst)):
                self.downloadFolder(localPath+folder, ftpPath+folder)            
        except Exception as r:
            print(traceback.format_exc())
            raise RuntimeError('The FTP server failed to download the file {}'.format(ftpPath))               
        else:
            print('Download folder {} OK'.format(ftpPath))
            
            
