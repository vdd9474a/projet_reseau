/* http://broux.developpez.com/articles/c/sockets/ */

#include "myTimer.h"
#include "fonc_sock.h"
#include "IOfichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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

	signal(SIGALRM, finTimer);
	alarm(TIMEOUT);
	for (i = 0; i < NB_GROUPE; i++)
	{
		comm[i] = receive_connection();
		nbComm++;
	}
	
	transfertFicher();

	return 0;

}

void transfertFicher()
{
	int i;
	int tailleF;
	int startR = 0;
	int finR;
	int start[NB_GROUPE] = {0};
	int end[NB_GROUPE] = {0};

	if (!nbComm)
	{
		fprintf(stderr, "aucune connexion!\n");
		exit(1);
	}

	printf("suite!\n");
	/* Lancement du transfert */
	for (i = 0; i < nbComm; i++)
	{
		emettreInt(comm[i], 0);
		tailleF = recevoirInt(comm[i]);
	}

	finR = tailleF;

	srand(time(NULL));
	printf("%d\n", (int) random()%(10));
	
	end[nbComm - 1] = tailleF;

	for (i = 0; i < nbComm; i++)
	{
		if (i > 0)
		{
			start[i] = end[i - 1];
		}
		if (i < nbComm - 1)
		{
			end[i] =  random()%(finR - startR) + startR;
			startR = end[i];
		}
	}

	for (i = 0; i < nbComm; i++)
	{
		emettreInt(comm[i], start[i]);
		emettreInt(comm[i], end[i]);
		printf("client %d, de %d octets à %d octets\n", i + 1, start[i], end[i]);
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
