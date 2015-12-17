/* http://broux.developpez.com/articles/c/sockets/ */

#include "myTimer.h"
#include "fonc_sock.h"
#include "IOfichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include <sys/stat.h>

#define NB_GROUPE 2
#define TIMEOUT 60

int comm[NB_GROUPE] = {0};
int nbComm = 0;

char * fichierSortie;

void transfertFicher();

void finTimer(int sig) {transfertFicher();}

int main (int argc, char ** argv)
{
	int i;
	char * adrIP;
	char nomDef[4] = "out";

	if (argc < 2)
	{
		fprintf(stderr, "USAGE : %s @IP_ecoute [nomFichier_sortie] !! \n", argv[0]);
		exit(1);
	}

	adrIP = argv[1];

	if (argc == 3)
		fichierSortie = argv[2];
	else
		fichierSortie = nomDef;


	deploiement_serveur(adrIP);

	//setTimer(60);
	signal(SIGALRM, finTimer);
	alarm(TIMEOUT);
	for (i = 0; i < NB_GROUPE; i++)
	{
		comm[i] = receive_connection();
		nbComm++;
	}
	//stopTimer();
	
	transfertFicher();

	return 0;

}

void transfertFicher()
{
	int i;
	int start[NB_GROUPE];
	int end[NB_GROUPE];

	if (!nbComm)
	{
		fprintf(stderr, "aucune connexion!\n");
		exit(1);
	}

	printf("suite!\n");
	/* Lancement du transfert */
	for (i = 0; i < nbComm; i++)
		emettreInt(comm[i], 0);

	for (i = 0; i < nbComm; i++)
	{
		start[i] = recevoirInt(comm[i]);
		end[i] = recevoirInt(comm[i]);
	}

	//emettreFichier("coffee.jpg", comm[0]);
	//emettrePartieFichier("coffee.jpg", comm[0], 0, 32000);
	for (i = 0; i < nbComm; i++)
	{
		recevoirPartieFichier(fichierSortie, comm[i], start[i], end[i]);
	}


	printf("Fichier recu!\n");

	for (i = 0; i < nbComm; i++)
		close_connexion(comm[i]);

	exit(0);
}
