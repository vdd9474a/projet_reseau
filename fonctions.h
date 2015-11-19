#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "erreur.h"

/*structure*/
typedef struct s_data * Data;


/*serveur*/
Data initData();

void deleteData(Data data);
void addFileInListFile(char * fileName, Data info);
void fileList(Data data);
void addAddress(Data info, char * addressRecieved);

/* Client*/
void initAddressTable(char ** table, int size);
void deleteAddessTable( char ** table, int size);
void addAddressInTable(char ** table, char * address);


#endif
