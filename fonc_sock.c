/* http://broux.developpez.com/articles/c/sockets/ */

#include "fonc_sock.h"
#include "myTimer.h"
#include "IOfichier.h"
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
#include <signal.h>
#include <time.h> 

#define NB_MEMBRE_GROUPE 3

#define MAXLOGINLEN 16
#define MAXHOSTLEN 64
#define MAXPORTLEN 6
#define MAXBUFFERLEN 1024
#define MAXDATALEN 1024*1000

#define SERVADDR "127.0.0.1"	/* Definition de l'adresse IP d'ecoute */
#define SERVPORT "9000"         /* Definition du port d'ecoute, si 0 port choisi dynamiquement */
#define LISTENLEN 23            /* Taille du tampon de demande de connexion */

#define TIMEMAX 60		/*duree du timer. Par defaut : 60 secondes*/


int descSockRDV;                /* Descripteur de socket de rendez-vous */
struct sockaddr_storage from;   /* Informations sur le client connecte */
socklen_t len;                  /* Variable utilisee pour stocker les */
char clientAddr[MAXHOSTLEN];    /* Adresse du client connecte sur le proxy */
char clientPort[MAXPORTLEN];    /* Port du client connete sur le proxy par le socket de communication */


int ouvreSocket(void)
{
	/*
     Initialisation de la socket de RDV IPv4/TCP
     socket serveur
	*/
    int descSock = socket(AF_INET, SOCK_STREAM, 0); 
    if (descSock == -1) 
    {   
        perror("Erreur Creation Socket RDV\n");
        exit(3);
    }   
    return (descSock);
}

void deploiement_serveur(void)
{
    /*pid_t idProc;*/
    /*bool darthVader = true;*/
    int ecode;                      /* Retour des fonctions */
    struct addrinfo *res_s;         /* Resultat de la fonction getaddrinfo */
    struct addrinfo hints;
    struct sockaddr_storage myinfo; /* Informations sur la connexion de RDV */
    /*int descSockCOM;*/        /* Descripteur de socket de communication */
    char proxyAddr[MAXHOSTLEN]; /* Adresse IP du proxy ftp */
    char proxyPort[MAXPORTLEN]; /* Port d'ecoute du proxy FTP */
    /*char buffer[MAXBUFFERLEN];      // buffer stockant les messages echanges entre le client et le serveur */
	

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
        exit(1);
    }

    /* Publication de la socket */
    ecode = bind(descSockRDV, res_s->ai_addr, res_s->ai_addrlen);
    if (ecode == -1)
    {
        perror("Erreur liaison de la socket de RDV");
        exit(3);
    }

    /* Nous n'avons plus besoin de cette liste chainee addrinfo */
    freeaddrinfo(res_s);

    /* Recupperation du nom de la machine et du numero de port pour affichage a l'ecran */
    len=sizeof(struct sockaddr_storage);
    ecode=getsockname(descSockRDV, (struct sockaddr *) &myinfo, &len);
    if (ecode == -1)
    {
        perror("SERVEUR: getsockname");
        exit(4);
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
        perror("Erreur initialisation buffer d'ecoute");
        exit(5);
    }

    len = sizeof(struct sockaddr_storage);

/*
    while (darthVader)
    {*/
        /*******************************
        * Attente connexion du client  *
        *******************************/
        /* Lorsque demande de connexion, creation d'une socket de communication avec le client */
       /*
		descSockCOM = accept(descSockRDV, (struct sockaddr *) &from, &len);
        if (descSockCOM == -1)
        {
            perror("Erreur accept\n");
            exit(6);
        }
        idProc = fork();
        switch (idProc)
        {
            case -1 :
                perror("impossible de forker()\n");
                exit(0);
            case 0 :
                darthVader = false;
				break;
			default:
				membre_groupe++;
				if (membre_groupe >= NB_MEMBRE_GROUPE) {membre_groupe = 0; groupe++;}
        }
    }
    ecode = getnameinfo((struct sockaddr*)&from, len, clientAddr,MAXHOSTLEN, clientPort, MAXPORTLEN, NI_NUMERICHOST | NI_NUMERICSERV);
    if (ecode != 0)
    {
            fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(ecode));
        exit(4);
    }
    printf("\n  port client : %s\n", clientPort);
    printf("    addr client : %s\n", clientAddr);
	printf("	groupe : %d\n", groupe);

	return descSockCOM;
	*/
}

int receive_connection()
{
	int descSockCOM, ecode;

	/*******************************
	* Attente connexion du client  *
	*******************************/
	/* Lorsque demande de connexion, creation d'une socket de communication avec le client */
	descSockCOM = accept(descSockRDV, (struct sockaddr *) &from, &len);
	if (descSockCOM == -1)
	{
		perror("Erreur accept\n");
		exit(6);
	}
    
	ecode = getnameinfo((struct sockaddr*)&from, len, clientAddr, MAXHOSTLEN, clientPort, MAXPORTLEN, NI_NUMERICHOST | NI_NUMERICSERV);
    if (ecode)
    {
            fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(ecode));
        exit(4);
    }
    printf("\n  port client : %s\n", clientPort);
    printf("    addr client : %s\n", clientAddr);

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
		fprintf(stderr, "Erreur, Host introuvable\n");
		exit(5);
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
		perror("probleme de lecture\n");
		exit(6);
	}
	buffer[ecode] = '\0';
	return buffer;
}

void close_connexion(int desc)
{
	close(desc);
}

void emettreFichier(char * nomF, int comm)
{
	int fich;
	int lu;
	Bloc bloc = creer_bloc();
	
	char res[32];

	sprintf(res, "%d", tailleFichier(nomF));
	write(comm, res, sizeof(res));

	fich = ouvrirFichier(nomF, LECTURE);
	
	while ((lu = read(fich, bloc, get_tailleBloc())) != 0)
	{
		write(comm, bloc, lu);
	}
	supprimer_bloc(bloc);
	fermerFichier(fich);
}

void recevoirFichier(char * nomF, int comm)
{
	int fich = creerFichier(nomF);
	int lu;
	int total_lu = 0;
	int taille;
	int t_bloc = get_tailleBloc();
	Bloc bloc = creer_bloc();

	char res[32];

	read(comm, res, sizeof(res));
	sscanf(res, "%d", &taille);

	while ((lu = read(comm, bloc, t_bloc)) != 0)
	{
		write(fich, bloc, lu);
		
		total_lu += lu;
		if (total_lu == taille)
			break;
	}
	supprimer_bloc(bloc);
	fermerFichier(fich);
}

void emettrePartieFichier(char * nomF, int comm, int octDeb, int octFin)
{
	int fich;
	int lu;
	int oct_a_lire = octFin - octDeb;
	int tailleBloc_a_lire = get_tailleBloc();
	Bloc bloc = creer_bloc();
	
	char res[32];

	sprintf(res, "%d", tailleFichier(nomF));
	write(comm, res, sizeof(res));

	fich = ouvrirFichier(nomF, LECTURE);

	lseek(fich, octDeb, SEEK_SET);
	
	if (oct_a_lire < tailleBloc_a_lire) {tailleBloc_a_lire = oct_a_lire;}

	while ((lu = read(fich, bloc, tailleBloc_a_lire)) != 0)
	{
		write(comm, bloc, lu);
		oct_a_lire -= lu;
		if (oct_a_lire < tailleBloc_a_lire) {tailleBloc_a_lire = oct_a_lire;}
	}
	supprimer_bloc(bloc);
	fermerFichier(fich);
}

void recevoirPartieFichier(char * nomF, int comm, int octDeb, int octFin)
{
	int fich = creerFichier(nomF);
	int lu;
	int total_lu = 0;
	int taille;
	int t_bloc = get_tailleBloc();
	Bloc bloc = creer_bloc();

	char res[32];

	read(comm, res, sizeof(res));
	sscanf(res, "%d", &taille);

	lseek(fich, 0, octDeb);

	while ((lu = read(comm, bloc, t_bloc)) != 0)
	{
		write(fich, bloc, lu);
		
		total_lu += lu;
		if (total_lu == taille)
			break;
	}
	supprimer_bloc(bloc);
	fermerFichier(fich);
}

void emettreTailleFichier(char * nomF, int comm)
{
	char res[32];

	sprintf(res, "%d", tailleFichier(nomF));
	write(comm, res, sizeof(res));
}

int recevoirInt(int comm)
{
	int taille;
	char res[32];

	read(comm, res, sizeof(res));
	sscanf(res, "%d", &taille);

	return taille;
}

void emettreInt(int comm, int i)
{
	char res[32];

	sprintf(res, "%d", i);
	write(comm, res, sizeof(res));
}
