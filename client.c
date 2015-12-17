/* fseek */

#include <stdio.h>
#include <stdlib.h>
#include "fonc_sock.h"
#include "IOfichier.h"

//#define MAXBUFFERLEN 255

int main (int argc, char * argv[])
{
	int numPort;
	int comm;
	int octDeb;
	int octFin;
	char * adrServ;
	char * nomF;

	if (argc != 4)
	{
		fprintf(stderr, "USAGE : %s @IP_serv num_port nomFichier octDeb octFin!", argv[0]);
		exit(1);
	}

	adrServ = argv[1];	/*Recuperation de l'adresse du serveur passé en parametre*/
	numPort = atoi(argv[2]);	/*Recuperation du numero de port pour la connexion au serveur (passé en parametre)*/
	nomF = argv[3];


	comm = connexion(adrServ, numPort);

	recevoirInt(comm); 

	emettreTailleFichier(nomF, comm);
	
	octDeb = recevoirInt(comm);
	octFin = recevoirInt(comm);

	emettrePartieFichier(nomF, comm, octDeb, octFin);
	//emettrePartieFichier("coffee.jpg", comm, 32001, tailleFichier("coffee.jpg"));

	//recevoirFichier("out.jpg", comm);
	//recevoirPartieFichier("out.jpg", comm, 0, 32000);

	printf("fichier %s emis de l'octet %d à %d!\n", nomF, octDeb, octFin);

	close_connexion(comm);

	return 0;
}
