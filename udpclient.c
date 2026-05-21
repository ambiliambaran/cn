#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];
    char response[1024];
    socklen_t len = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket failed");
        exit(1);
    }

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&server, len);

    printf("Message sent to server\n");

    memset(response, 0, sizeof(response));

    recvfrom(sockfd, response, sizeof(response) - 1, 0,
             (struct sockaddr *)&server, &len);

    printf("Message from server: %s\n", response);

    close(sockfd);
    return 0;
}
