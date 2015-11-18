#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "erreur.h"

<<<<<<< HEAD
=======

>>>>>>> e783d1339e40b54c91397389c5a92319a5186ddf
/*structure*/
typedef struct s_data * Data;


/*serveur*/
<<<<<<< HEAD

=======
>>>>>>> e783d1339e40b54c91397389c5a92319a5186ddf
Data initData();

void deleteData(Data data);
void addFileInListFile(char * fileName, Data info);
void fileList(Data data);
void addAddress(Data info, char * addressRecieved);

/* Client*/

<<<<<<< HEAD
void initAddressTable(char ** table, int size);
=======
void initAddressTable(char ** table);
>>>>>>> e783d1339e40b54c91397389c5a92319a5186ddf
void deleteAddessTable( char ** table, int size);
void addAddressInTable(char ** table, char * address);


#endif
