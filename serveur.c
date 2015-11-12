//http://broux.developpez.com/articles/c/sockets/

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>

#define NB_MEMBRE_GROUPE 3

#define MAXLOGINLEN 16
#define MAXHOSTLEN 64
#define MAXPORTLEN 6
#define MAXBUFFERLEN 1024
#define MAXDATALEN 1024*1000

#define SERVADDR "127.0.0.1"            // Definition de l'adresse IP d'ecoute
#define SERVPORT "9000"                    // Definition du port d'ecoute, si 0 port choisi dynamiquement
#define LISTENLEN 23                    // Taille du tampon de demande de connexion


 /* Fonction qui ouvre un socket
  * retourne le descripteur du socket
  */
int ouvreSocket(void);

int main (void)
{
    pid_t idProc;
    bool darthVader = true;
    int ecode;                      // Retour des fonctions
    struct addrinfo *res_s;         // Resultat de la fonction getaddrinfo
    struct addrinfo hints;
    struct sockaddr_storage myinfo; // Informations sur la connexion de RDV
    struct sockaddr_storage from;   // Informations sur le client connecte
    socklen_t len;                  // Variable utilisee pour stocker les 
    int descSockRDV;                // Descripteur de socket de rendez-vous
    int descSockCOM;        // Descripteur de socket de communication
    char proxyAddr[MAXHOSTLEN]; // Adresse IP du proxy ftp
    char proxyPort[MAXPORTLEN]; // Port d'ecoute du proxy FTP
    char clientAddr[MAXHOSTLEN];    // Adresse du client connecte sur le proxy
    char clientPort[MAXPORTLEN];    // Port du client connete sur le proxy par le socket de communication
    //char buffer[MAXBUFFERLEN];      // buffer stockant les messages echanges entre le client et le serveur

//----------------------------------------------------

    descSockRDV = ouvreSocket();

//----------a voir
    // Publication de la socket au niveau du système
    // Assignation d'une adresse IP et un numero de port
    // Mise a zero de hints
    memset(&hints, 0, sizeof(hints));
    // Initailisation de hints
    hints.ai_flags = AI_PASSIVE;        // mode serveur, nous allons utiliser la fonction bind
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_family = AF_INET;          // seules les adresses IPv4 seront presentees par 
                            // la fonction getaddrinfo

    // Recuperation des informations du serveur
    ecode = getaddrinfo(SERVADDR, SERVPORT, &hints, &res_s);
    if (ecode)
    {
        fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(ecode));
        exit(1);
    }

    // Publication de la socket
    ecode = bind(descSockRDV, res_s->ai_addr, res_s->ai_addrlen);
    if (ecode == -1)
    {
        perror("Erreur liaison de la socket de RDV");
        exit(3);
    }

    // Nous n'avons plus besoin de cette liste chainee addrinfo
    freeaddrinfo(res_s);

    // Recupperation du nom de la machine et du numero de port pour affichage a l'ecran
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
    // Definition de la taille du tampon contenant les demandes de connexion
    ecode = listen(descSockRDV, LISTENLEN);
    if (ecode == -1)
    {
        perror("Erreur initialisation buffer d'ecoute");
        exit(5);
    }

    len = sizeof(struct sockaddr_storage);

    while (darthVader)
    {
        /*******************************
        * Attente connexion du client  *
        *******************************/
        // Lorsque demande de connexion, creation d'une socket de communication avec le client
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
        }
    }
    ecode = getnameinfo((struct sockaddr*)&from, len, clientAddr,MAXHOSTLEN, clientPort, MAXPORTLEN, NI_NUMERICHOST | NI_NUMERICSERV);
    if (ecode != 0)
    {
            fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(ecode));
        exit(4);
    }
    printf("\n  port client : %s\n", clientPort);
    printf("    addr client : %s\n\n", clientAddr);

	
	/*
	int sock;	//descripteur socket

	sock = ouvreSocket();


	//fermeture socket
	close(sock);
	*/
	return 0;
}

int ouvreSocket(void)
{
    // Initialisation de la socket de RDV IPv4/TCP
    // socket serveur
    int descSock = socket(AF_INET, SOCK_STREAM, 0); 
    if (descSock == -1) 
    {   
        perror("Erreur Creation Socket RDV\n");
        exit(3);
    }   
    return (descSock);
}
