import ActivityInterface_pb2
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 42069))
s.listen(1)


while True:
    print("Listening")
    conn, addr = s.accept()
    print(addr)
    message = s.recv(1000)
    print(message)

