#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char sender[100], receiver[100], message[500], response[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2500);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Enter Sender Email: ");
    scanf("%s", sender);

    printf("Enter Receiver Email: ");
    scanf("%s", receiver);

    printf("Enter Message: ");
    getchar();
    fgets(message, sizeof(message), stdin);

    send(sockfd, sender, sizeof(sender), 0);
    send(sockfd, receiver, sizeof(receiver), 0);
    send(sockfd, message, sizeof(message), 0);

    recv(sockfd, response, sizeof(response), 0);

    printf("Server Response: %s\n", response);

    close(sockfd);

    return 0;
}