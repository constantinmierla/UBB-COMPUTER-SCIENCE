#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void deservire_client(int c) {
    uint16_t size1, size2;

    recv(c, &size1, sizeof(size1), MSG_WAITALL);
    size1 = ntohs(size1);

    int *sir1 = (int*)malloc(size1 * sizeof(int));
    if (sir1 == NULL) {
        perror("Eroare la alocarea memoriei");
        close(c);
        exit(1);
    }

    for (int i = 0; i < size1; i++) {
        uint16_t elem;
        recv(c, &elem, sizeof(elem), MSG_WAITALL);
        sir1[i] = ntohs(elem);
    }
    int *sir2 = (int*)malloc(size2 * sizeof(int));
    recv(c, &size2, sizeof(size2), MSG_WAITALL);
    size2 = ntohs(size2);
    if(sir2 == NULL) {
	perror("Eroare la alocarea memoriei");
	close(c);
	exit(1);
    }
    for (int i = 0; i < size2; i++) {
        uint16_t elem;
        recv(c, &elem, sizeof(elem), MSG_WAITALL);
        sir2[i] = ntohs(elem);
    }

    printf("Elementele primului sir: ");
    for (int i = 0; i < size1; i++) {
        printf("%d ", sir1[i]);
    }
    printf("\n");

    printf("Elementele celui de-al doilea sir: ");
    for (int i = 0; i < size2; i++) {
        printf("%d ", sir2[i]);
    }
    printf("\n");

    int *result = (int*)malloc(size1 * sizeof(int));
    int count = 0;
    for (int i = 0; i < size1; i++) {
        int found = 0;
        for (int j = 0; j < size2; j++) {
            if (sir1[i] == sir2[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[count++] = sir1[i];
        }
    }

    uint16_t result_count = htons(count);
    send(c, &result_count, sizeof(result_count), 0);
    for (int i = 0; i < count; i++) {
        uint16_t elem = htons(result[i]);
        send(c, &elem, sizeof(elem), 0);
    }

    free(sir1);
    free(sir2);
    free(result);
    close(c);
}

int main() {
    int s;
    struct sockaddr_in server, client;
    int c, l;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Eroare la crearea socketului server");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Eroare la bind");
        return 1;
    }

    listen(s, 5);
    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        c = accept(s, (struct sockaddr *)&client, &l);
        printf("S-a conectat un client.\n");
        if (fork() == 0) {
            close(s);
            deservire_client(c);
            return 0;
        }
        close(c);
    }
}
