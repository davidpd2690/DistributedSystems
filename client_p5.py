# coding=utf-8
import socket
import threading
import random
import os
import requests 
import json

def clima(ciudad):

    api_key = '4c3d1f4ba4d2f1f2822b21acc33a3f23'
    url = "http://api.openweathermap.org/data/2.5/weather?"
    nombreCiudad = ciudad 
    URLrequest = url + "appid=" + api_key + "&q=" + nombreCiudad + "&units=metric" 
    response = requests.get(URLrequest) 

    #convierte json a formato para python
    respuesta = response.json() 

    if respuesta["cod"] != "404": 

	    mainKey = respuesta['main'] 
	    temp = mainKey["temp"] 
	    humedad = mainKey["humidity"] 
	    clima = respuesta["weather"] 

	    print(" Temperatura = " + str(temp) + " C°" +
		        "\n humedad = " + str(humedad) + "%")
		     
    else: 
	    print("No se encontró la ciudad")


def ReceiveData(sock):
    while True:
        try:
            data,addr = sock.recvfrom(1024)
            print(data.decode('utf-8'))
        except:
            pass

def RunClient(serverIP):
    host = socket.gethostbyname(socket.gethostname())
    puerto = random.randint(6000,10000)
    server = (str(serverIP),5000)
    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    s.bind((host,puerto))

    nombre = raw_input('Ingresa tu nombre: ')
    print('CONECTADO...')
    if nombre == '':
        nombre = raw_input('Por favor ingresa un nombre:')
    s.sendto(nombre.encode('utf-8'),server)
    threading.Thread(target=ReceiveData,args=(s,)).start()
    while True:
        data = raw_input()
        if data == 'salir':
            break
        elif data=='':
            continue
        elif data == 'clima':
            ciudad = raw_input('Ingresa la ciudad de la que quieres saber el clima: ')
            climm = clima(ciudad)
            #print('Obteniendo el clima de ' + ciudad + ' para ' + nombre)
            climaReq = '[SERVER]-> ' + nombre + ' ha pedido el clima actual para ' + ciudad
            s.sendto(climaReq.encode('utf-8'),server)
            continue
        data = '['+nombre+']-> '+ data
        s.sendto(data.encode('utf-8'),server)
    s.sendto(data.encode('utf-8'),server)
    s.close()
    os._exit(1)

#dirIP = raw_input('Ingresa IP de servidor: ')
RunClient("127.0.0.1")
