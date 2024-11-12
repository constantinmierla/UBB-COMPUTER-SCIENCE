#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a, b;
  uint32_t suma;

  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.25.15.99");

  printf("Introduceti cele 2 numere\n");
  printf("Primul numar: ");
  scanf("%hu", &a);
  printf("Al doilea numar : ");
  scanf("%hu", &b);

  a = htons(a);
  b = htons(b);

  sendto(c, &a, sizeof(a), 0, (struct sockaddr *) &server, sizeof(server));
  sendto(c, &b, sizeof(b), 0, (struct sockaddr *) &server, sizeof(server));

  printf("Am trimis\n");

  recvfrom(c, &suma, sizeof(suma), MSG_WAITALL, (struct sockaddr *) &server, sizeof(server));
  suma = ntohl(suma);

  printf("Suma din client este %u\n", suma);
  close(c);
}
