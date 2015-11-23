#include <stdio.h>
#include <stdlib.h>
#include "fonc_sock.h"

#define MAXBUFFERLEN 255

int main (int argc, char * argv[])
{
	int numPort;
	char * adrServ;
	int desc;
	char buffer[MAXBUFFERLEN];

	if (argc != 3)
	{
		fprintf(stderr, "USAGE : %s @IP_serv num_port !", argv[0]);
		exit(1);
	}

	adrServ = argv[1];	/*Recuperation de l'adresse du serveur passé en parametre*/
	numPort = atoi(argv[2]);	/*Recuperation du numero de port pour la connexion au serveur (passé en parametre)*/

	desc = connexion(adrServ, numPort);

	printf("%s\n", ecoute_reponse(desc, buffer));

	return 0;
}
