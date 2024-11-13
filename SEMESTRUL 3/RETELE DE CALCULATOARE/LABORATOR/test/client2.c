#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 256

uint16_t hton_custom(uint16_t val) {
    //return (val << 8) | (val >> 8);
    return htons(val);
}

uint16_t ntoh_custom(uint16_t val) {
    //return (val << 8) | (val >> 8);
    return ntohs(val);
}

int main() {
    int tcp_socket, udp_socket;
    struct sockaddr_in server_addr, partner_udp_addr, client_udp_addr;
    uint16_t udp_port;

    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("Eroare la crearea socketului TCP");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(tcp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Introdu portul UDP pentru client: ");
    scanf("%hu", &udp_port);
    udp_port = hton_custom(udp_port);
    send(tcp_socket, &udp_port, sizeof(udp_port), 0);

    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&client_udp_addr, 0, sizeof(client_udp_addr));
    client_udp_addr.sin_family = AF_INET;
    client_udp_addr.sin_port = ntoh_custom(udp_port);
    client_udp_addr.sin_addr.s_addr = INADDR_ANY;
    bind(udp_socket, (struct sockaddr *)&client_udp_addr, sizeof(client_udp_addr));

    recv(tcp_socket, &partner_udp_addr.sin_addr, sizeof(partner_udp_addr.sin_addr), 0);
    recv(tcp_socket, &partner_udp_addr.sin_port, sizeof(partner_udp_addr.sin_port), 0); //????
    partner_udp_addr.sin_family = AF_INET;

    printf("Partenerul este la IP %s si port UDP %d\n",
           inet_ntoa(partner_udp_addr.sin_addr), ntohs(partner_udp_addr.sin_port));

    char message[BUFFER_SIZE];
    int num_local, num_received;
    socklen_t partner_addr_len = sizeof(partner_udp_addr);

    while (1) {
        printf("Introdu un numar: ");
        scanf("%d", &num_local);

        // Trimitere numar partenerului prin UDP
        sprintf(message, "%d", num_local);
        sendto(udp_socket, message, strlen(message) + 1, 0,
               (struct sockaddr *)&partner_udp_addr, partner_addr_len);

        // Primire numar de la partener
        recvfrom(udp_socket, message, BUFFER_SIZE, 0,
                 (struct sockaddr *)&partner_udp_addr, &partner_addr_len);
        num_received = atoi(message);
        printf("Numar primit de la partener: %d\n", num_received);

        if (num_local == num_received) {
            printf("Numerele coincid. Conexiunea se va inchide.\n");
            break;
        }
    }

    close(tcp_socket);
    close(udp_socket);
    return 0;
}
