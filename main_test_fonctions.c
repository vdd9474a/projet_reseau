#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "fonctions.h"
#include "erreur.h"

int main()
{
	/*******************************/
	/*test des diférentes fonctions*/
	/*******************************/
	
	/*intitialisation d'un structure Data*/
	Data test_data = initData();
	
	if(test_data!=NULL)
		printf("initalisation de la strucutre test_data s'est bien passee\n");
	else
		Erreur("initalisation de la strucutre test_data",99);
	
	addFileInListFile("test.txt", test_data);
	printf("fichier est bien ajouté dans la structure\n");
	
	printf("le fichier ajouté est ");
	fileList(test_data);
	
	printf("supression de la structure...\n");
	deleteData(test_data);
	
	return 0;
}
