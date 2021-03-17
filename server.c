#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

int main() 
{ 
    int server_sockfd, client_sockfd; 
    int server_len, client_len; 
    struct sockaddr_in server_address;	// Socket del server 
    struct sockaddr_in client_address;  // Socket del cliente

    /* Crear un socket sin nombre para el server */ 
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    /* Nombrar el socket del server */ 
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);  
    server_address.sin_port = htons(9734); 
    server_len = sizeof(server_address); 

	// Asociar la IP por la que escucho y el puerto con el socket "server_sockfd"
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len); 
	
	// Escuchar en el socket "server_sockfd"
    listen(server_sockfd, 5); 
    while(1) { 
        char ch; 
        printf("server waiting\n"); 
		
		// Aceptar la conexi�n del cliente
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len); 
        read(client_sockfd, &ch, 1); 
	 	printf("Procesando peticion del cliente\n");
		sleep(5);
        ch++; 
        write(client_sockfd, &ch, 1); 
        close(client_sockfd); 
    } 
} 
