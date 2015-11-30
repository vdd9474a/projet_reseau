/* http://broux.developpez.com/articles/c/sockets/ */

#include "fonc_sock.h"
#include "IOfichier.h"
#include <stdio.h>

int main (void)
{
	int comm = deploiement_serveur();
	int fich = ouvrirFichier("lena_color.gif", LECTURE);
	int test = creerFichier("test.gif");
	//int taille_bloc = get_tailleBloc();
	int lu;
	Bloc bloc_data = creer_bloc();

	do
	{
		lu = lire_blocFichier(fich, bloc_data);
		ecrire_blocFichier(test, bloc_data);
		printf("%d-", lu);
	} while (lu != 0);

	printf("\nsend!\n");

	do
	{
		lu = lire_blocFichier(fich, bloc_data);
		ecrire_blocFichier(comm, bloc_data);
		printf("%d-", lu);
	} while (lu != 0);

	printf("Fichier envoye!\n");

	close_connexion(comm);
}
