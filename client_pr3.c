#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    char name[30];
    
    /* Crear un socket para el cliente */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* Nombrar el socket, de acuerdo con el server */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    
    if(result == -1) 
    {
        perror("oops: client1");
        exit(1);
    }
    
    printf("ingresa tu nombre de usuario:\n");
    scanf("%s", name);
    write(sockfd, &name, 1);
    read(sockfd, &name, 1);
    printf("name: = %s\n", name);


    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}