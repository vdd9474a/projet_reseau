#ifndef __FONC_SOCK_H
#define __FONC_SOCK_H

/* Fonction qui met en place un serveur, et attent un connexion.
 * Retourne descripteur socket de la connexion en cours (communiquation)
 */
void deploiement_serveur();

/* Fonction bloquante qui attend une connexion
 * Retourne le descripteur de socket
 */
int receive_connection();

 /* Fonction qui ecrit dans le socket
  */
void ecrit_socket(int desc, char * message);

 /* Fonction qui ouvre un socket
  * retourne le descripteur du socket
  */
int ouvreSocket(void);

 /* Fonction qui se connect à une adresse et un port
  * retourne le descripteur de socket
  */
int connexion(char * adrServ, int numPort);

 /* Fonction qui lit des donnees sur un socket
  * retourne la chaine de caractère lu
  */
char * ecoute_reponse(int desc, char * buffer);

 /* Fonction qui ferme une connexion
  */
void close_connexion(int desc);

/* Fonction qui transfert le fichier nomF sur le descripteur de fichier comm (socket?)
 */
void emettreFichier(char * nomF, int comm);

/* Fonction qui recoit un fichier par le descripteur comm (socket?) et qui creer le fichier nomF
 */
void recevoirFichier(char * nomF, int comm);

/* Fonction qui transfert une partie d'un fichier d'un octet a un autre specifie en parametre (octDeb a octFin)
 */
void emettrePartieFichier(char * nomF, int comm, int octDeb, int octFin);

/* Fonction qui recoit une partie d'un fichier d'un octet a un autre specifie en parametre (octDeb a octFin)
 */
void recevoirPartieFichier(char * nomF, int comm, int octDeb, int octFin);

#endif
