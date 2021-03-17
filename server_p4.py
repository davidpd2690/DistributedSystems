# coding=utf-8
import socket 
import select 
import sys
import xml.etree.ElementTree as ET 
from thread import start_new_thread


server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

msgexito = "conexión exitosa al cliente"
#bytesToSend = str.encode(msgexito)

IP_address = "127.0.0.1"
Port = 9734

server.bind((IP_address, Port)) 
print("servidor esperando...")

server.listen(10) 

list_of_clients = [] 

def clientthread(conn, addr): 

	while True: 
			try: 
				bytesAddressPair = server.recvfrom(1024)
				message = bytesAddressPair[0]
				addr = bytesAddressPair[1]
#				#message = conn.recv(2048) 
				if message: 

					print addr + ": " + message 
					message_to_send = addr + ": " + message
					broadcast(message_to_send, conn)
				else: 
					
					remove(conn) 

			except: 
				continue
#					for clients in list_of_clients: 
#						if clients!=connection: 
#							try: 
#								clients.sendto(bytesToSend, addr) 
#							except: 
#								clients.close() 
#								remove(clients) 
#								else: 
#									remove(conn) 
#			except: 
#				continue
#
#
#				while True: 
#			try: 
#				message = conn.recv(2048) 
#				if message: 
#
#					print addr[0] + ": " + message 
#
#					message_to_send = addr[0] + ": " + message 
#					broadcast(message_to_send, conn) 
#
#				else: 
#					
#					remove(conn) 
#
#			except: 
#				continue

def broadcast(message, connection): 
	for clients in list_of_clients: 
		if clients!=connection: 
			try: 
				clients.sendto(message) 
			except: 
				clients.close() 
				remove(clients) 

def remove(connection): 
	if connection in list_of_clients: 
		list_of_clients.remove(connection) 

while True: 

	conn, addr = server.accept() 
	list_of_clients.append(conn) 
	print addr[0] + "conectado"
	start_new_thread(clientthread,(conn,addr))	 

conn.close() 
server.close() 
