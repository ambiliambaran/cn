#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    FILE *fp;
    int bytes;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Waiting for connection...\n");
    client_socket = accept(server_fd, NULL, NULL);

    fp = fopen("received_file.txt", "w");

    while((bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytes, fp);
    }

    printf("File received successfully.\n");

    fclose(fp);
    close(client_socket);
    close(server_fd);

    return 0;
}