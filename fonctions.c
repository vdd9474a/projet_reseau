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

void initAddressTable(char ** table, int size)
{
  int i;
  table = malloc(sizeof *table * 2);
  
  for (i = 0; i < 2; i++)
  {
    table[i] = malloc(sizeof **table * 17);
    
  }
  size = 2;
}

void deleteAddessTable( char ** table, int size)
{
  int i;
  
  for(i = 0; i < size; i++)
  {
    free(table[i]);  
  }
  
  free(table);
}

void addAddressInTable(char ** table, char * address)
{

}

