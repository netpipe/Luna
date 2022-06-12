# Cross-platform asynchronous version of subprocess.Popen
# Copyright (c) 2011 James Buchwald
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

'''
Provides an asynchronous wrapper around the subprocess module.

This is based on a code snippet by J. F. Sebastian, posted at StackOverflow
at the following URL: http://stackoverflow.com/questions/375427/
'''

from subprocess import PIPE, Popen
from threading  import Thread, Lock
from warnings import warn

from collections import deque

class AsyncPopen(Popen):
    '''
    Asynchronous wrapper around subprocess.Popen.
    
    Do not directly access AsyncPopen.stdout, AsyncPopen.stderr, or
    AsyncPopen.stdin.  Instead, use the (non-blocking asynchronous)
    AsyncPopen.communicate() method.
    
    This reads entire lines from stdout and stderr at once.
    
    Based on a code snippet by J. F. Sebastian, found at the following URL: 
        http://stackoverflow.com/questions/375427/
    '''
    def __init__(self, args, bufsize=0, executable=None,
                 stdin=None, stdout=None, stderr=None,
                 preexec_fn=None, close_fds=False, shell=False,
                 cwd=None, env=None, universal_newlines=False,
                 startupinfo=None, creationflags=0):
        '''
        Creates a new AsyncPopen instance.
        
        All of the arguments are the same as for subprocess.Popen with several
        exceptions:
            * stdin, stdout, and stderr can only be None or PIPE.
        
        In Python 3, all data read from stdout and stderr will be treated as
        the "bytes" built-in type; it is up to the user to convert this type
        to the appropriate character type, if desired.
        '''
        # Check for use of stdin, stdout, stderr values other than NONE, PIPE
        if stdin != None and stdin != PIPE:
            warn("stdin must be either None or subprocess.PIPE.")
            _stdin = None
        else:
            _stdin = stdin
        if stdout != None and stdout != PIPE:
            warn("stdout must be either None or subprocess.PIPE.")
            _stdout = None
        else:
            _stdout = stdout
        if stderr != None and stderr != PIPE:
            warn("stderr must be either None or subprocess.PIPE.")
            _stderr = None
        else:
            _stderr = stderr
        
        # Inherit base class behavior.
        super(AsyncPopen, self).__init__(args, bufsize=bufsize,
                                         executable=executable, stdin=_stdin,
                                         stdout=_stdout, stderr=_stderr,
                                         preexec_fn=preexec_fn,
                                         close_fds=close_fds,
                                         shell=shell, cwd=cwd, env=env,
                                         universal_newlines=universal_newlines,
                                         startupinfo=startupinfo,
                                         creationflags=creationflags)
        
        # Start the I/O polling threads.
        self.use_stdout = False
        '''Flag to use stdout.'''
        self.use_stderr = False
        '''Flag to use stderr.'''
        self.use_stdin = False
        '''Flag to use stdin.'''
        if _stdout == PIPE:
            self.use_stdout = True
            self.stdout_queue = deque()
            '''Queue of data read from stdout.'''
            self.stdout_lock = Lock()
            '''Lock used for stdout queue synchronization.'''
            self.stdout_thread = Thread(target=self._ThreadedOutputQueue,
                                        args=(self.stdout, self.stdout_queue,
                                              self.stdout_lock))
            '''Queue management thread for stdout.'''
            self.stdout_thread.daemon = True
            self.stdout_thread.start()
        if _stderr == PIPE:
            self.use_stderr = True
            self.stderr_queue = deque()
            '''Queue of data read from stderr.'''
            self.stderr_lock = Lock()
            '''Lock used for stderr queue synchronization.'''
            self.stderr_thread = Thread(target=self._ThreadedOutputQueue,
                                        args=(self.stderr, self.stderr_queue,
                                              self.stderr_lock))
            '''Queue management thread for stderr.'''
            self.stderr_thread.daemon = True
            self.stderr_thread.start()
        if _stdin == PIPE:
            self.use_stdin = True
            self.stdin_queue = deque()
            '''Queue of data to write to stdin.'''
            self.stdin_lock = Lock()
            '''Lock used for stdin queue synchronization.'''
            self.stdin_thread = Thread(target=self._ThreadedInputQueue,
                                        args=(self.stdin, self.stdin_queue,
                                              self.stdin_lock))
            '''Queue management thread for stdin.'''
            self.stdin_thread.daemon = True
            self.stdin_thread.start()
    
    def _ThreadedOutputQueue(self, pipe, queue, lock):
        '''
        Called from the thread to update an output (stdout, stderr) queue.
        '''
        try:
            while True:
                chunk = pipe.readline()
                if not chunk:
                    # hit end-of-file
                    break
                lock.acquire()
                queue.append(chunk)
                lock.release()
        except:
            pass
        finally:
            pipe.close()
    
    def _ThreadedInputQueue(self, pipe, queue, lock):
        '''
        Called from the thread to update an input (stdin) queue.
        '''
        try:
            while True:
                lock.acquire()
                while len(queue) > 0:
                    chunk = queue.popleft()
                    pipe.write(chunk)
                lock.release()
                pipe.flush()
        except:
            pass
        finally:
            pipe.close()
    
    def communicate(self, input=None):
        '''
        Interact with process: Enqueue data to be sent to stdin.  Return data
        read from stdout and stderr as a tuple (stdoutdata, stderrdata).  Do
        NOT wait for process to terminate.
        '''
        if self.use_stdin and input:
            # enqueue data
            self.stdin_lock.acquire()
            self.stdin_queue.append(input)
            self.stdin_lock.release()
        
        stdoutdata = None
        stderrdata = None
        if self.use_stdout:
            # get data
            data = b""
            self.stderr_lock.acquire()
            try:
                while len(self.stdout_queue) > 0:
                    data += self.stdout_queue.popleft()
            except:
                self.stderr_lock.release()
                raise
            self.stderr_lock.release()
            if data: stdoutdata = data

        if self.use_stderr:
            # get data
            data = b""
            self.stderr_lock.acquire()
            try:
                while len(self.stderr_queue) > 0:
                    data += self.stderr_queue.popleft()
            except:
                self.stderr_lock.release()
                raise
            self.stderr_lock.release()
            if data: stderrdata = data
        
        return (stdoutdata, stderrdata)
