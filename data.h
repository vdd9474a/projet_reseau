#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
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

void initAddressTable(char ** table);
void deleteAddessTable( char ** table);
void addAddressInTable(char ** table, char * address);
void listFilesInDir(char * dir);

#endif
