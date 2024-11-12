#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
  int s, l;
  struct sockaddr_in server, client;
  uint16_t a, b;
  uint32_t suma;

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
  while(1){
    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    recvfrom(s, &a, sizeof(b), MSG_WAITALL, (struct sockaddr *) &client, &l);
    a = ntohs(a);

    recvfrom(s, &b, sizeof(b), MSG_WAITALL, (struct sockaddr *) &client, &l);
    b = ntohs(b);
    printf("Am primit numerele: %hu, %hu\n", a, b);

    suma = a + b;
    printf("Am trimis suma %u\n", suma);
    suma = htonl(suma);
    sendto(s, &suma, sizeof(suma), 0, (struct sockaddr *) &client, sizeof(client));
   }
    close(s);

}
