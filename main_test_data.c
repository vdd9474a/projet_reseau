#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "data.h"
#include "erreur.h"

int main()
{
	int i;/**/
	/******************************************************/
	/*test des diférentes fonctions sur la structure data */
	/******************************************************/
	
	/*intitialisation d'un structure Data*/
	Data test_data = initData();
	
	/*intitialisation d'une liste de chaine de caractere*/
	char ** testTable = initAddressTable();/**/
	
	if(test_data!=NULL)
		printf("initalisation de la strucutre test_data s'est bien passee\n");
	else
		erreur("initalisation de la strucutre test_data",99);
	
	addFileInListFile("test", test_data);
	printf("fichier est bien ajouté dans la structure\n");
	printf("le fichier ajouté est ");
	fileList(test_data);
	addFileInListFile("test2", test_data);
	printf("fichier est bien ajouté dans la structure\n");
	printf("le fichier ajouté est ");
	fileList(test_data);
	addFileInListFile("test3", test_data);
	printf("fichier est bien ajouté dans la structure\n");
	printf("le fichier ajouté est ");
	fileList(test_data);
	
	printf("supression de la structure...\n");
	deleteData(test_data);
	printf("structure suprimée\n");
	
	/***********************************************************/
	/*test des diférentes fonctions sur la liste des adresse IP*/
	/***********************************************************/
	if(testTable!=NULL)
	  printf("initalisation de le tableau d'adresse IP s'est bien passee\n");
	else
	  erreur("erreur lors de l'initialisation de la strucutre test_data",99);
	
	for(i=0;i<6;i++)
	{
	  addAddressInTable(testTable, "TEST");
	  printf("adresse %d est bien ajoutee\n",i);
	}
	
	for(i=0;i<6;i++)
	{
	  addAddressInTable(testTable, "TEST");
	  printf("adresse %d est bien ajoutee\n",i);
	}
	
	
	printf("supression du tableau d'adresse IP\n");
	deleteAddessTable(testTable);/**/
	
	return 0;
}
