#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr;
    char sender[100], receiver[100], message[500];
    FILE *fp;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2500);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("SMTP Server Waiting...\n");

    client_socket = accept(server_fd, NULL, NULL);

    recv(client_socket, sender, sizeof(sender), 0);
    recv(client_socket, receiver, sizeof(receiver), 0);
    recv(client_socket, message, sizeof(message), 0);

    fp = fopen("mailbox.txt", "a");

    fprintf(fp, "From: %s\n", sender);
    fprintf(fp, "To: %s\n", receiver);
    fprintf(fp, "Message: %s\n", message);
    fprintf(fp, "-------------------------\n");

    fclose(fp);

    send(client_socket, "Mail Sent Successfully", 22, 0);

    printf("Mail stored in mailbox.txt\n");

    close(client_socket);
    close(server_fd);

    return 0;
}