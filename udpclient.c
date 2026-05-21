#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_len = sizeof(server_addr);

    while(1) {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;   // remove Enter

        sendto(sockfd, buffer, strlen(buffer)+1, 0,
        (struct sockaddr*)&server_addr, addr_len);

         memset(buffer, 0, sizeof(buffer));
         recvfrom(sockfd, buffer, sizeof(buffer)-1, 0,
         (struct sockaddr*)&server_addr, &addr_len);

         printf("Server: %s\n", buffer);        
    }

    close(sockfd);
    return 0;
}
