import threading
import time
import unittest

#qthread
class StoppableThread(threading.Thread):
    def __init__(self):
        super(StoppableThread, self).__init__()
        self.daemon = True
        self.running = threading.Event()
        self.running.set()
        self.__has_shutdown = False
        
    def run(self):
        '''Overloads the threading.Thread.run'''
        # Call the User's Startup functions
        self.startup()
        
        # Loop until the thread is stopped
        while self.isRunning():
            self.mainloop()
            
        # Clean up
        self.cleanup()
        
        # Flag to the outside world that the thread has exited
        # AND that the cleanup is complete
        self.__has_shutdown = True
        
    def stop(self):
        self.running.clear()
        
    def isRunning(self):
        return self.running.isSet()
        
    def isShutdown(self):
        return self.__has_shutdown
        

    ###############################
    ### User Defined Functions ####
    ###############################
    
    def mainloop(self):
       raise NotImplementedError 

    def startup(self):
        pass
        
    def cleanup(self):
        pass


# Test / Usage of the stoppable thread
class MyThreadingClass(StoppableThread):
    def __init__(self, a):
        super(MyThreadingClass, self).__init__()
        self.a = a
        self.b = "World"
        self.delay = .5 # seconds
        
    def startup(self):
        # Overload the startup function
        print "My Thread Starting Up..."
        
    def cleanup(self):
        # Overload the cleanup function
        print "My Thread Is Shutting Down..."
        # Close files, ports, etc...
        time.sleep(2)
        print "Cleanup Complete!"
        
    def mainloop(self):
        # Some routine to be called over and over
        # ie: reading ports or sockets
        print self.a + " " + self.b

        # Throttling needs to be done here if the
        # primary function is not blocking
        time.sleep(self.delay)


class TestStoppableThread(unittest.TestCase):        
    def test_QuickTest(self):
        thread = MyThreadingClass("Hello")
        thread.start()
        time.sleep(2)
        thread.stop()
        time.sleep(3)
        self.assertTrue(thread.isShutdown())
        
if __name__ == "__main__":
    unittest.main()
            
