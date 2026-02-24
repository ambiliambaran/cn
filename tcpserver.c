#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_fd, 5);
    printf("Server waiting for connection...\n");

    addr_size = sizeof(client_addr);
    client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);

    while(1) {
        read(client_socket, buffer, sizeof(buffer));
        printf("Client: %s\n", buffer);

        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);

        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    close(server_fd);

    return 0;
}
