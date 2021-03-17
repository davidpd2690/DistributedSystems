import socket 
import select 
import sys 


server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
 
IP_address = "127.0.0.1" 
Port = 9734 
server.connect((IP_address, Port)) 
name = raw_input("Ingresa tu nombre de usuario: ")

while True: 
	
	sockets_list = [sys.stdin, server] 

	read_sockets,write_socket, error_socket = select.select(sockets_list,[],[]) 

	for socks in read_sockets:
		if socks == server:
			message = socks.recv(2048)
			print message
		else:
		    message = sys.stdin.readline()
		    server.send(message)
		    sys.stdout.write(name +": ")
		    sys.stdout.write(message)
		    sys.stdout.flush()
 
