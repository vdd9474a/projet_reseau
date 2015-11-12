#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


//structure
Data infoClient;


//serveur
Data initData();

void addFileInListFile(char * fileName, Data info);

void addAddress(Data info, char * addressRecieved);

// Client
void addAddressInTable(char ** table, char * address)

#endif
