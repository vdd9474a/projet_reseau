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
/* Structure servant*/
typedef struct s_data * Data;


/*serveur*/

/* Fonction d'initialisation d'une structure Data
 * retourne une stracture Data initialisee
 */
Data initData();

/* Fonction qui detruit en mémoire la structure data en parametre 
 */
void deleteData(Data data);

/* Fonction qui ajoute un nom de fichier dans le tableau de nom de fichier de la structure Data mise en parametre
 */
void addFileInListFile(char * fileName, Data info);

/* Fonction qui liste les fichiers presents dans la structure mise en parametre.
 * Utilise pour les tests.
 */
void fileList(Data data);

/* Fonction qui ajoute l'adresse IP du client dans la structure mise en parametre
 */
void addAddress(Data info, char * addressRecieved);

/* Client*/

/* Fonction qui initialise un tableau de chaine de caractere mis en parametre
*/
void initAddressTable(char ** table);

/* Fonction qui detruit en memoire le tableau de chaine de caractere mis en parametre
 */
void deleteAddessTable( char ** table);

/* Fonction qui ajoute l'adresse IP des autres client (mmis en parametre) dans un tableau d'adresse IP (chaine de caractere) mis en parametre
 */
void addAddressInTable(char ** table, char * address);

/* Fonction qui renvoie le nombre d'octet a envoyer en comptant les caracteres a envoyer
 */
int listFilesInDir(char * dir);

#endif
