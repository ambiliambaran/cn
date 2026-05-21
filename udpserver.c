#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    printf("Server waiting for data...\n");

    addr_size = sizeof(client_addr);

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                 (struct sockaddr*)&client_addr, &addr_size);

        printf("Client: %s", buffer);

        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&client_addr, addr_size);
    }

    close(sockfd);
    return 0;
}
