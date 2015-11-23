#ifndef __FONC_SOCK_H
#define __FONC_SOCK_H

/* Fonction qui met en place un serveur, et attent un connexion.
 * Retourne descripteur socket de la connexion en cours (communiquation)
 */
int deploiement_serveur();

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

#endif
