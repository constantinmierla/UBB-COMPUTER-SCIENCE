#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t n1, n2;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("192.168.223.128");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("Introduceti dimensiunea primului sir\n");
  scanf("%hu", &n1);
  
  while (n1 <= 0)
  {
	printf("Reintroduceti o dimensiune > 0 : \n");
        scanf("%hu", &n1);
  }
  uint16_t sir1[n1];
  
  printf("Introduceti elementele primului sir\n");

  for(int i = 0; i < n1; i++)
  {
	scanf("%hu", &sir1[i]);
	sir1[i] = htons(sir1[i]);
  }

  printf("Introduceti dimensiunea celui de al doilea sir\n");
  scanf("%hu", &n2);
  
  while (n2 <= 0)
  {
   printf("Reintroduceti o dimensiune mai mare strict decat 0 : \n");
   scanf("%hu", &n2);
  }
  uint16_t sir2[n2];
  printf("Introduceti elementele celui de al doilea sir\n");

  for(int i = 0; i < n2; i++)
  {
        scanf("%hu", &sir2[i]);
        sir2[i] = htons(sir2[i]);
  }

  n1 = htons(n1);
  n2 = htons(n2);
  send(c, &n1, sizeof(n1), 0);

  send(c, sir1, sizeof(sir1), 0);
  send(c, &n2, sizeof(n2), 0);
  send(c, sir2, sizeof(sir2), 0);

  uint16_t nr_rez;
  recv(c, &nr_rez, sizeof(nr_rez), 0);

  nr_rez = ntohs(nr_rez);
  uint16_t rez[nr_rez];
  recv(c, rez, nr_rez*sizeof(uint16_t), 0);

  for (int i = 0; i < nr_rez; i++)
  {
	rez[i] = ntohs(rez[i]);
  }

  printf("Sirul este: ");

  for(int i = 0; i < nr_rez; i++)
  {
	printf("%hu ", rez[i]);
  }
  printf("\n");
  close(c);
}
