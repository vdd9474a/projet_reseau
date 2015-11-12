#include "fonctions.h"


typedef struct _data
{
  char addr[17];
  char listeFichiers[128];
} *Data;


Data initData()
{
	Data info = malloc(sizeof(struct _data));
	return info
}

void addFileInListFile(char * fileName, Data info)
{
    strcpy(inf->listeFichiers,fileName);
}

void addAddress(Data info, char * addressRecieved)
{
  strcpy(inf->addr,addressRecieved);
}

void addAddressInTable(char ** table, char * address)
{
  
}