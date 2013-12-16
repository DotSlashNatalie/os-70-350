import threading
import sys

class mythread(threading.Thread):
    def run(self):
        for i in range(0, 10):
            sys.stdout.write(str(i) + "\n")
        
try:
    thread1 = mythread()
    thread2 = mythread()
    
    thread1.start()
    thread2.start()
    
    thread1.join()
    thread2.join()
except:
    print "Could not create threads!"