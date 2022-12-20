#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BACKLOG 10

int main(int argc, char *argv[])
{
    int server_fd, client_fd, valread;
    struct sockaddr_in server, client;
    int opt = 1;
    int addrlen = sizeof(client);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((client_fd = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while(client_fd){
    	valread = read(client_fd, buffer, 1024);
    	printf("Received %d bytes: %s\n", valread, buffer);
	char vuln[15];
	strcpy(vuln, buffer);
    	send(client_fd, hello, strlen(hello), 0);
    	printf("Sent %ld bytes: %s\n", strlen(hello), hello);
    }

    return 0;
}
