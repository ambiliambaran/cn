#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    FILE *fp;
    int bytes;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    fp = fopen("send_file.txt", "r");

    while((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        send(sockfd, buffer, bytes, 0);
    }

    printf("File sent successfully.\n");

    fclose(fp);
    close(sockfd);

    return 0;
}