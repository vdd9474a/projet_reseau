/* http://broux.developpez.com/articles/c/sockets/ */

#include "fonc_sock.h"
#include "IOfichier.h"
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>

int main (void)
{
	int comm = deploiement_serveur();

	emettreFichier("coffee.jpg", comm);

	printf("Fichier envoye!\n");

	close_connexion(comm);
}
