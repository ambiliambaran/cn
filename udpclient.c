#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_size = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&server_addr, addr_size);

        memset(buffer, 0, sizeof(buffer));

        recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                 (struct sockaddr*)&server_addr, &addr_size);

        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
