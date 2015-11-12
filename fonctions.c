#include "fonctions.h"


typedef struct s_data
{
  char addr[17];
  char listeFichiers[128];
} t_data;


Data initData()
{
	Data info = malloc(sizeof(struct s_data));
	return info;
}

void deleteData(Data data)
{
  free(data);
}


void addFileInListFile(char * fileName, Data info)
{
    strcpy(info->listeFichiers,fileName);
}

void addAddress(Data info, char * addressRecieved)
{
  strcpy(info->addr,addressRecieved);
}

void initAddressTable(char ** table)
{
  
}

void addAddressInTable(char ** table, char * address)
{
//   if( table[0][0] == NULL
}
