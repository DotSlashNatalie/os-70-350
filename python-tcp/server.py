import time
import socket
import thread

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1", 8085))
s.listen(1)

def func():
    while True:
        conn, addr = s.accept()
        data = conn.recv(1024)
        conn.send("Hello, the current timestamp is - " + str(int(time.time())))
        conn.close()

thread.start_new_thread(func, ())
while True:
    pass
#while True:
#    conn, addr = s.accept()
#    data = conn.recv(1024)
#    conn.send("Hello, the current timestamp is - " + str(int(time.time())))
#    conn.close()