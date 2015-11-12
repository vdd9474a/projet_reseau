#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>

#define MAXBUFFERLEN 255

void test(char * adrServ, int numPort);

int ouvreSocket(void);
void adresse_host(char * adrServ, struct hostent * adress_en_char);

int main (int argc, char * argv[])
{
	int numPort;
	char * adrServ;

	if (argc != 3)
	{
		fprintf(stderr, "USAGE : %s @IP_serv num_port !", argv[0]);
		exit(1);
	}

	adrServ = argv[1];	//Recuperation de l'adresse du serveur passé en parametre
	numPort = atoi(argv[2]);	//Recuperation du numero de port pour la connexion au serveur (passé en parametre)

	test(adrServ, numPort);

	return 0;
}

void test(char * adrServ, int numPort)
{
	struct sockaddr_in serv_addr;
	struct hostent * server;
	int sockfd = ouvreSocket();
	//int err;
	//char * buffer = (char *)malloc(sizeof(MAXBUFFERLEN + 1));

	//strcat(fichDem, "\r\r\n\n");

	server = gethostbyname(adrServ);
	if (server == NULL)
	{
		fprintf(stderr, "Erreur, Host introuvable\n");
		exit(5);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(numPort);

	if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
		fprintf(stderr, "ERROR connecting");
		  
	 
	//write(sockfd, fichDem, strlen(fichDem));

	/*
	do {
		err = read(sockfd, buffer, MAXBUFFERLEN);
		buffer[err] = '\0';
		//printf("%s/", buffer);
		write(fichDest, buffer, err);
	} while (err == MAXBUFFERLEN);
	
	if (err == -1) {fprintf(stderr, "erreur recup info");exit(6);}
	*/

	close(sockfd);
}

int ouvreSocket(void)
{
	int descSock = socket(AF_INET, SOCK_STREAM, 0);
	if (descSock == -1)
	{
		fprintf(stderr, "Erreur Creation Socket\n");
		exit(4);
	}
	return (descSock);
}
