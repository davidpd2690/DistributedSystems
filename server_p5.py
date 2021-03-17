import socket
import threading
import Queue



def RecvData(sock,recvPackets):
    while True:
        data,addr = sock.recvfrom(1024)
        recvPackets.put((data,addr))

def RunServer():
    host = "127.0.0.1"
    puerto = 5000
    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    s.bind((host,puerto))
    clients = set()
    recvPackets = Queue.Queue()

    print('Servidor conectado, esperando clientes...')

    threading.Thread(target=RecvData,args=(s,recvPackets)).start()

    while True:
        while not recvPackets.empty():
            data,addr = recvPackets.get()
            if addr not in clients:
                clients.add(addr)
                continue
            clients.add(addr)
            data = data.decode('utf-8')
            if data.endswith('salir'):
                clients.remove(addr)
                continue
            print(str(data))
            for c in clients:
                if c!=addr:
                    s.sendto(data.encode('utf-8'),c)
    s.close()

RunServer()