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

void transfertFicher();

void finTimer(int sig) {transfertFicher();}

int main (void)
{
	int i;

	deploiement_serveur();

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
	int part1;
	int part2;

	if (!nbComm)
	{
		fprintf(stderr, "aucune connexion!\n");
		exit(1);
	}

	printf("suite!\n");

	part1 = recevoirInt(comm[0]);
	part2 = recevoirInt(comm[1]);


	//emettreFichier("coffee.jpg", comm[0]);
	//emettrePartieFichier("coffee.jpg", comm[0], 0, 32000);
	if (nbComm > 1)
	{

		recevoirPartieFichier("out1.jpg", comm[0], 0, part1);
		recevoirPartieFichier("out2.jpg", comm[1], part1 , part1 + part2);
	}


	printf("Fichier recu!\n");

	for (i = 0; i < nbComm; i++)
		close_connexion(comm[i]);

	exit(0);
}
