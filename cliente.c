#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

int main() 
{ 
    int sockfd; 
    int len; 
    struct sockaddr_in address; 
    int result; 
    char ch='a'; 

    /* Crear un socket para el cliente */ 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
 
    /* Nombrar el socket, de acuerdo con el server */ 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    address.sin_port = htons(9734); 
    len = sizeof(address); 
	
	// Conectar el socket creado a la dirección IP:Puerto que establecimos previamente
    result = connect(sockfd, (struct sockaddr *)&address, len); 
    if(result == -1) { 
        perror("oops: client1"); 
        exit(1); 
    }
    write(sockfd, &ch, 1); 		// Escribir en el socket
    read(sockfd, &ch, 1); 		// Leer la respuesta del socket
    printf("char from server = %c\n", ch); 
    close(sockfd); 
    exit(0); 
} 
