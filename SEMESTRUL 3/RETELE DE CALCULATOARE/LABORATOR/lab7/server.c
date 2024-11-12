#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define TCP_PORT 8080

typedef struct {
    struct sockaddr_in addr;
    int udp_port;
    int tcp_sock;
} ClientInfo;

ClientInfo clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    ClientInfo client = *(ClientInfo *)arg;
    char buffer[BUFFER_SIZE];
    int len;

    while ((len = recv(client.tcp_sock, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[len] = '\0';
        
        if (strcmp(buffer, "by") == 0) {
            printf("Client %s disconnected\n", inet_ntoa(client.addr.sin_addr));
            break;
        }
        
        printf("Message from client %s: %s\n", inet_ntoa(client.addr.sin_addr), buffer);

        // Broadcast message to other clients via UDP
        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < client_count; i++) {
            if (clients[i].tcp_sock != client.tcp_sock) {
                int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
                struct sockaddr_in udp_addr = clients[i].addr;
                udp_addr.sin_port = htons(clients[i].udp_port);

                sendto(udp_sock, buffer, len, 0, (struct sockaddr *)&udp_addr, sizeof(udp_addr));
                close(udp_sock);
            }
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    // Remove client from list
    close(client.tcp_sock);
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].tcp_sock == client.tcp_sock) {
            clients[i] = clients[client_count - 1];
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    free(arg);
    return NULL;
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);
    printf("TCP server started on port %d\n", TCP_PORT);

    while (1) {
        ClientInfo *client = malloc(sizeof(ClientInfo));
        socklen_t client_len = sizeof(client->addr);
        client->tcp_sock = accept(server_sock, (struct sockaddr *)&client->addr, &client_len);

        // Receive UDP port from client
        recv(client->tcp_sock, &client->udp_port, sizeof(client->udp_port), 0);
        client->udp_port = ntohs(client->udp_port);

        printf("New client connected: %s on UDP port %d\n", inet_ntoa(client->addr.sin_addr), client->udp_port);

        pthread_mutex_lock(&clients_mutex);
        clients[client_count++] = *client;
        pthread_mutex_unlock(&clients_mutex);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client);
        pthread_detach(tid);
    }

    close(server_sock);
    return 0;
}

