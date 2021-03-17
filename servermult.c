#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdlib.h>
#include <unistd.h> 

int main() 
{ 
    int server_sockfd, client_sockfd; 
    int server_len, client_len; 
    struct sockaddr_in server_address; 
    struct sockaddr_in client_address; 
	
	// Crear el socket del server
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	// Nombrar el socket que es indicar de que IP aceptará conexiones y en que puerto
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_address.sin_port = htons(9734); 
	
	// Asociar el socket del server con el IP y puerto que indicamos anteriormente
    server_len = sizeof(server_address); 
    bind(server_sockfd,(struct sockaddr *)&server_address,server_len); 

    /* Crear una cola de conexiones, ignorar detalles de la salida del 
       hijo y espera a los clientes */ 
    listen(server_sockfd, 5); 
    signal(SIGCHLD, SIG_IGN); // Indicar que las señales de los hijos las ignore
    while(1) { 
        char ch; 
        printf("server waiting\n"); 

        /* Aceptar conexión */ 
        client_sockfd = accept(server_sockfd,(struct sockaddr *)
                        &client_address, &client_len); 

        /* Crea un proceso hijo, prueba el fork para ver cuando estamos en el
           padre o cuando estamos en el hijo */ 
        if(fork() == 0) { 
            /* Si estamos en el hijo, podemos leer y escribir al cliente en
               client_sockfd, el delay de 5 segundos es solo para la
               demostración */
            read(client_sockfd, &ch, 1); 
            sleep(5); 
            ch++; 
            write(client_sockfd, &ch, 1); 
            close(client_sockfd); 
            exit(0); 	// Termina el hijo que atendió la petición del cliente
        } 

        /* De otra manera, estamos en el padre y nuestro trabajo para 
        este cliente ha terminado */ 
        else { 
            close(client_sockfd); 
        } 
    } 
} 
