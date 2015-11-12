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

void get(char * adrServ, int numPort, char * fichDem, int fichDest);
void put(char * adrServ, int numPort, char * fichDem, int fichDest);
void test(char * adrServ, int numPort, char * fichDem, int fichDest);

int ouvreSocket(void);
void adresse_host(char * adrServ, struct hostent * adress_en_char);

int main (int argc, char * argv[])
{
	int numPort;
	char * adrServ;
	char * fichDem;
	int fichDest;

	if (argc <= 4 || argc >= 7)
	{
		fprintf(stderr, "USAGE : %s get|put|test @IP_serv num_port fich_demande [fich_dst]!", argv[0]);
		exit(1);
	}

	adrServ = argv[2];	//Recuperation de l'adresse du serveur passé en parametre
	numPort = atoi(argv[3]);	//Recuperation du numero de port pour la connexion au serveur (passé en parametre)
	fichDem = argv[4];	//Recuperation du fichier a demander passé en parametre


	if (argc == 5) {fichDest = 1;}
	else 
	{
		fichDest = open(argv[5], O_WRONLY|O_CREAT, 0644);
		if (fichDest == -1)
		{
			fprintf(stderr, "Impossible de creer un fichier pour enregistrer la page!");
			exit(2);
		}
	}


	if (strcmp("get", argv[1]) == 0) {get(adrServ, numPort, fichDem, fichDest);}
	else if (strcmp("put", argv[1]) == 0) {put(adrServ, numPort, fichDem, fichDest);}
	else if (strcmp("test", argv[1]) == 0) {test(adrServ, numPort, fichDem, fichDest);}
	else 
	{
		fprintf(stderr, "USAGE : get|put|test %s @IP_serv num_port fich_demande [fich_dst]!", argv[0]);
		exit(3);
	}

	return 0;
}

void get(char * adrServ, int numPort, char * fichDem, int fichDest)
{
	struct sockaddr_in serv_addr;
	struct hostent * server;
	int sockfd = ouvreSocket();
	int err;
	//char * buffer = (char *)malloc(sizeof(MAXBUFFERLEN + 1));
	char buffer;
	int compt = 0;
	

	char * msg = (char *) malloc(256);
	sprintf(msg,"GET /%s HTTP/1.0\nAccept : text/html\nAccept : text/plain\nUser-Agent : Lynx/2.4 libwww/2.1.4\r\r\n\n", fichDem);

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
		  
	 
	write(sockfd,msg,strlen(msg));
	
	do {
		err = read(sockfd, &buffer, 1);
		write(1, &buffer, 1);
		if ((buffer == '\r' && compt % 2 == 0) || (buffer == '\n' && compt % 2 != 0))
			compt++;
		else {compt = 0;}
	} while (compt < 4);

	do {
		err = read(sockfd, &buffer, 1);//MAXBUFFERLEN);
		//buffer[err] = '\0';
		write(fichDest, &buffer, 1);//err);
	} while (err);// == MAXBUFFERLEN);
	
	if (err == -1) {fprintf(stderr, "erreur recup info");exit(6);}
	close(sockfd);
}

void put(char * adrServ, int numPort, char * fichDem, int fichDest)
{
	struct sockaddr_in serv_addr;
	struct hostent * server;
	int sockfd = ouvreSocket();
	int err;
	int fichSend;
	int taille_fichier;
	//char * buffer = (char *)malloc(sizeof(MAXBUFFERLEN + 1));
	char data;
	
	fichSend = open(fichDem, O_RDONLY);
	if (fichSend == -1)
	{
		fprintf(stderr, "erreur lors de l'ouverture du fichier à envoyer\n");
		exit(4);
	}

	taille_fichier = lseek(fichSend, 0, SEEK_END);
	lseek(fichSend, 0, SEEK_SET);
	if (taille_fichier == -1)
	{
		fprintf(stderr, "Erreur lors de la lecture de la taille du fichier\n");
		exit(5);
	}

	char * msg = (char *) malloc(256);
	sprintf(msg,"PUT /%s HTTP/1.0\nContent-length : %d\r\r\n\n", fichDem, taille_fichier);

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
		  
	 
	write(sockfd,msg,strlen(msg));

	while (taille_fichier > 0)
	{
		err = read(fichSend, &data, 1);
		write(sockfd, &data, 1);
		taille_fichier--;
	}

	do {
		err = read(sockfd, &data, 1);
		write(1, &data, 1);
	} while (err);
	
	close(sockfd);
}

void test(char * adrServ, int numPort, char * fichDem, int fichDest)
{
	struct sockaddr_in serv_addr;
	struct hostent * server;
	int sockfd = ouvreSocket();
	int err;
	char * buffer = (char *)malloc(sizeof(MAXBUFFERLEN + 1));

	strcat(fichDem, "\r\r\n\n");

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
		  
	 
	write(sockfd, fichDem, strlen(fichDem));

	do {
		err = read(sockfd, buffer, MAXBUFFERLEN);
		buffer[err] = '\0';
		//printf("%s/", buffer);
		write(fichDest, buffer, err);
	} while (err == MAXBUFFERLEN);
	
	if (err == -1) {fprintf(stderr, "erreur recup info");exit(6);}
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
