#include "IOfichier.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int TAILLEBLOC = 256;

typedef unsigned char s_bloc;

Bloc creer_bloc()
{
	Bloc bloc = (Bloc) malloc(sizeof(s_bloc)*TAILLEBLOC);
	return bloc;
}

void supprimer_bloc(Bloc bloc)
{
	free(bloc);
}

void set_tailleBloc(int taille)
{
	TAILLEBLOC = taille;
}

int get_tailleBloc()
{
	return TAILLEBLOC;
}

void lire_blocFichier(int desc, Bloc bloc)
{
	read(desc, bloc, TAILLEBLOC);
}

void ecrire_blocFichier(int desc, Bloc bloc)
{
	write(desc, bloc, TAILLEBLOC);
}

int ouvrirFichier(char * nomF, int mode)
{
	return open(nomF,mode);
}

void fermerFichier(int desc)
{
	close(desc);
}
