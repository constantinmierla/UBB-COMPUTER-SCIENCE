#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 8080
#define UDP_PORT 12345  // Portul UDP al clientului

void *receive_udp_messages(void *arg) {
    int udp_sock = *(int *)arg;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in udp_addr;
    socklen_t addr_len = sizeof(udp_addr);

    while (1) {
        int len = recvfrom(udp_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&udp_addr, &addr_len);
        buffer[len] = '\0';
        printf("UDP message received: %s\n", buffer);
    }
}

int main() {
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // IP-ul serverului

    connect(tcp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Trimitem portul UDP către server
    int udp_port = htons(UDP_PORT);
    send(tcp_sock, &udp_port, sizeof(udp_port), 0);

    // Configurăm socket-ul UDP pentru a primi mesaje
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in udp_addr;
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(UDP_PORT);
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr));

    pthread_t udp_thread;
    pthread_create(&udp_thread, NULL, receive_udp_messages, &udp_sock);
    pthread_detach(udp_thread);

    char buffer[BUFFER_SIZE];
    while (1) {
        printf("Enter a message (or 'by' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Eliminăm newline

        send(tcp_sock, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "by") == 0) {
            printf("Closing connection...\n");
            break;
        }

        sleep(5); // Pauză între mesaje
    }

    close(tcp_sock);
    close(udp_sock);
    return 0;
}
