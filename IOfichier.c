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

int lire_blocFichier(int desc, Bloc bloc)
{
	return read(desc, bloc, TAILLEBLOC);
}

void ecrire_blocFichier(int desc, Bloc bloc)
{
	write(desc, bloc, sizeof(bloc));
}

int creerFichier(char * nomF)
{
	return creat(nomF, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int ouvrirFichier(char * nomF, int mode)
{
	return open(nomF,mode);
}

void fermerFichier(int desc)
{
	close(desc);
}
