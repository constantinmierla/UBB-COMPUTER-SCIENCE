#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;

  s = socket(AF_INET, SOCK_STREAM, 0);
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

  listen(s, 5);

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while (1) {
    uint16_t n1,n2;
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");


    recv(c, &n1, sizeof(n1), MSG_WAITALL);
    recv(c, &n2, sizeof(n2), MSG_WAITALL);

    n1 = ntohs(n1);
    n2 = ntohs(n2);

    uint16_t sir1[n1], sir2[n2];

    recv(c, &sir1, n1 * sizeof(uint16_t), MSG_WAITALL);
    recv(c, &sir2, n2 * sizeof(uint16_t), MSG_WAITALL);

    for (int i = 0; i < n1; i++)
    {
	sir1[i] = ntohs(sir1[i]);
    }

    for (int i = 0; i < n2; i++)
    {
	sir2[i] = ntohs(sir2[i]);
    }

    uint16_t rezultat[n1];
    int k = 0;

    for (int i = 0; i < n1; i++)
    {
	int gasit = 0;
	for (int j = 0; j < n2; j++)
	{
		if(sir1[i] == sir2[j])
		{
			gasit = 1;
			break;
		}
	}
	if(!gasit)
	{
		rezultat[k++] = htons(sir1[i]);
	}
    }

    uint16_t nr_rez = htons(k);
    send(c, &nr_rez, sizeof(nr_rez), 0);

    send(c, rezultat, k * sizeof(uint16_t), 0);


    close(c);
    printf("Done.\n");

  }
}
