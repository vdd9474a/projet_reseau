/* http://broux.developpez.com/articles/c/sockets/ */

#include "fonc_sock.h"
#include "erreur.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <strings.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>

#define NB_MEMBRE_GROUPE 3

#define MAXLOGINLEN 16
#define MAXHOSTLEN 64
#define MAXPORTLEN 6
#define MAXBUFFERLEN 1024
#define MAXDATALEN 1024*1000

#define SERVADDR "127.0.0.1"	/* Definition de l'adresse IP d'ecoute */
#define SERVPORT "9000"         /* Definition du port d'ecoute, si 0 port choisi dynamiquement */
#define LISTENLEN 23            /* Taille du tampon de demande de connexion */

#define GROUPE 3


int ouvreSocket(void)
{
	/*
     Initialisation de la socket de RDV IPv4/TCP
     socket serveur
	*/
    int descSock = socket(AF_INET, SOCK_STREAM, 0); 
    if (descSock == -1) 
    {   
        erreur("Erreur Creation Socket RDV\n", 1);
    }   
    return (descSock);
}

int deploiement_serveur(void)
{
    pid_t idProc;
    bool darthVader = true;
    int ecode;                      /* Retour des fonctions */
    struct addrinfo *res_s;         /* Resultat de la fonction getaddrinfo */
    struct addrinfo hints;
    struct sockaddr_storage myinfo; /* Informations sur la connexion de RDV */
    struct sockaddr_storage from;   /* Informations sur le client connecte */
    socklen_t len;                  /* Variable utilisee pour stocker les */
    int descSockRDV;                /* Descripteur de socket de rendez-vous */
    int descSockCOM;        /* Descripteur de socket de communication */
    char proxyAddr[MAXHOSTLEN]; /* Adresse IP du proxy ftp */
    char proxyPort[MAXPORTLEN]; /* Port d'ecoute du proxy FTP */
    char clientAddr[MAXHOSTLEN];    /* Adresse du client connecte sur le proxy */
    char clientPort[MAXPORTLEN];    /* Port du client connete sur le proxy par le socket de communication */
    /*char buffer[MAXBUFFERLEN];      // buffer stockant les messages echanges entre le client et le serveur */
	

	int groupe = 1;
	int membre_groupe = 0;

/*---------------------------------------------------- */

    descSockRDV = ouvreSocket();

/*----------a voir */
	/*
    Publication de la socket au niveau du système
    Assignation d'une adresse IP et un numero de port
    Mise a zero de hints
	*/
    memset(&hints, 0, sizeof(hints));
    /* Initailisation de hints */
    hints.ai_flags = AI_PASSIVE;        /* mode serveur, nous allons utiliser la fonction bind */
    hints.ai_socktype = SOCK_STREAM;    /* TCP */
    hints.ai_family = AF_INET;          /* seules les adresses IPv4 seront presentees par la fonction getaddrinfo */

    /* Recuperation des informations du serveur */
    ecode = getaddrinfo(SERVADDR, SERVPORT, &hints, &res_s);
    if (ecode)
    {
        fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(ecode));
		exit(3);
    }

    /* Publication de la socket */
    ecode = bind(descSockRDV, res_s->ai_addr, res_s->ai_addrlen);
    if (ecode == -1)
    {
        erreur("Erreur liaison de la socket de RDV", 3);
    }

    /* Nous n'avons plus besoin de cette liste chainee addrinfo */
    freeaddrinfo(res_s);

    /* Recupperation du nom de la machine et du numero de port pour affichage a l'ecran */
    len=sizeof(struct sockaddr_storage);
    ecode=getsockname(descSockRDV, (struct sockaddr *) &myinfo, &len);
    if (ecode == -1)
    {
        erreur("SERVEUR: getsockname", 4);
    }
    ecode = getnameinfo((struct sockaddr*)&myinfo, sizeof(myinfo), proxyAddr,MAXHOSTLEN, proxyPort, MAXPORTLEN, NI_NUMERICHOST | NI_NUMERICSERV);
    if (ecode != 0)
    {
        fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(ecode));
        exit(4);
    }
    printf("\nL'adresse d'ecoute est: %s\n", proxyAddr);
    printf("Le port d'ecoute est: %s\n", proxyPort);
    /* Definition de la taille du tampon contenant les demandes de connexion */
    ecode = listen(descSockRDV, LISTENLEN);
    if (ecode == -1)
    {
        erreur("Erreur initialisation buffer d'ecoute", 5);
    }

    len = sizeof(struct sockaddr_storage);

    while (darthVader)
    {
        /*******************************
        * Attente connexion du client  *
        *******************************/
        /* Lorsque demande de connexion, creation d'une socket de communication avec le client */
        descSockCOM = accept(descSockRDV, (struct sockaddr *) &from, &len);
        if (descSockCOM == -1)
        {
            erreur("Erreur accept\n", 6);
        }
        idProc = fork();
        switch (idProc)
        {
            case -1 :
                erreur("impossible de forker()\n", 7);
            case 0 :
                darthVader = false;
				break;
			default:
				membre_groupe++;
				if (membre_groupe >= GROUPE) {membre_groupe = 0; groupe++;}
        }
    }
    ecode = getnameinfo((struct sockaddr*)&from, len, clientAddr,MAXHOSTLEN, clientPort, MAXPORTLEN, NI_NUMERICHOST | NI_NUMERICSERV);
    if (ecode != 0)
    {
		fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(ecode));
        exit(8);
    }
    printf("\n  port client : %s\n", clientPort);
    printf("    addr client : %s\n", clientAddr);
	printf("	groupe : %d\n", groupe);

	return descSockCOM;
}

void ecrit_socket(int desc, char * message)
{
	write(desc, message, strlen(message));
}

int connexion(char * adrServ, int numPort)
{
	struct sockaddr_in serv_addr;
	struct hostent * server;
	int sockfd = ouvreSocket();

	server = gethostbyname(adrServ);
	if (server == NULL)
	{
		erreur("Erreur, Host introuvable\n", 9);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(numPort);

	if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
		fprintf(stderr, "ERROR connecting");
		  
	return sockfd;
}

char * ecoute_reponse(int desc, char * buffer)
{
	int ecode = read(desc, buffer, MAXBUFFERLEN);
	if (ecode == -1)
	{
		erreur("probleme de lecture\n", 10);
	}
	buffer[ecode] = '\0';
	return buffer;
}

void close_connexion(int desc)
{
	close(desc);
}
