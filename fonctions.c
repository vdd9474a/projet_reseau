#include "fonctions.h"


typedef struct _data
{
	string addr;
	char ** listeFichiers;
} *Data;

Data initData()
{
	Data info = malloc(sizeof(struct _data));
	info->listeFichier = NULL;
	return info
}

void addFileInListFile(char * fileName, Data info)
{
	if (info->listeFichier == NULL)
	{
		info->listeFichier = (*char)malloc(sizeof(*char));
		info->listeFichier[0] =	malloc((strlen(fileName)+1)*sizeof(char));
		info->listeFichier[0] = fileName;
	}


}

