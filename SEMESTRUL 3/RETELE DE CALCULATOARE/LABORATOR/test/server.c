#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 256

typedef struct {
    int tcp_socket;
    struct sockaddr_in addr;
    uint16_t udp_port;
} ClientInfo;

ClientInfo clients[MAX_CLIENTS];
int client_count = 0;

void handle_client_pair(ClientInfo client1, ClientInfo client2);

int main() {
    int tcp_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Crearea socket-ului TCP pentru server
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("Eroare la crearea socketului TCP");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Realizarea bind pe socketul TCP
    if (bind(tcp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Eroare la bind pe TCP");
        close(tcp_socket);
        exit(1);
    }

    listen(tcp_socket, MAX_CLIENTS);

    printf("Serverul este pregatit si asteapta clienti...\n");

    while (1) {
        int client_socket = accept(tcp_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Eroare la acceptarea conexiunii");
            continue;
        }

        uint16_t client_udp_port;
        recv(client_socket, &client_udp_port, sizeof(client_udp_port), 0);
	client_udp_port = ntohs(client_udp_port);

	printf("UDP PORT primit:  %hu\n", client_udp_port);
        clients[client_count].tcp_socket = client_socket;
        clients[client_count].addr = client_addr;
        clients[client_count].udp_port = client_udp_port;
        client_count++;

        // Daca sunt doi clienti, se imperecheaza
        if (client_count % 2 == 0) {
            ClientInfo client1 = clients[client_count - 2];
            ClientInfo client2 = clients[client_count - 1];

            if (fork() == 0) {
                handle_client_pair(client1, client2);
                close(client_socket);
                exit(0);
            }
        }
    }

    close(tcp_socket);
    return 0;
}

void handle_client_pair(ClientInfo client1, ClientInfo client2) {
    printf("Trimitem catre client 1: %s:%hu\n", inet_ntoa(client2.addr.sin_addr), client2.udp_port);
    printf("Trimitem catre client 2: %s:%hu\n", inet_ntoa(client1.addr.sin_addr), client1.udp_port);
	// trimiterea informatiilor de conectare partenerilor
    send(client1.tcp_socket, &client2.addr.sin_addr, sizeof(client2.addr.sin_addr), 0);
    send(client1.tcp_socket, &client2.udp_port, sizeof(client2.udp_port), 0);

    send(client2.tcp_socket, &client1.addr.sin_addr, sizeof(client1.addr.sin_addr), 0);
    send(client2.tcp_socket, &client1.udp_port, sizeof(client1.udp_port), 0);

    printf("clientii imperecheati: %s:%d si %s:%d\n",
           inet_ntoa(client1.addr.sin_addr), client1.udp_port,
           inet_ntoa(client2.addr.sin_addr), client2.udp_port);

    close(client1.tcp_socket);
    close(client2.tcp_socket);
}
