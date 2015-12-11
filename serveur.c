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
	alarm(30);
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

	printf("suite!\n");

	emettreFichier("coffee.jpg", comm[0]);

	printf("Fichier envoye!\n");

	for (i = 0; i < nbComm; i++)
		close_connexion(comm[i]);

	exit(0);
}
