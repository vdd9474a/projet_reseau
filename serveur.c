/* http://broux.developpez.com/articles/c/sockets/ */

#include "fonc_sock.h"
#include "IOfichier.h"
#include <stdio.h>
#include <unistd.h>

int main (void)
{
	int comm = deploiement_serveur();

	emettreFichier("config.txt", comm);

	printf("Fichier envoye!\n");

	close_connexion(comm);
}
