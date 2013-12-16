import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 8085))
s.send("Hello")
data = s.recv(1024)
s.close()

print data