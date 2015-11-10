#include <stdio.h>
#include <string.h>

#define NB_MEMBRE_GROUPE 3

 /* Fonction qui ouvre un socket
  * retourne le descripteur du socket
  */
int ouvreSocket(void)

int main (void)
{
	return 0;
}

int ouvreSocket(void)
{
    // Initialisation de la socket de RDV IPv4/TCP
    // socket serveur
    int descSock = socket(AF_INET, SOCK_STREAM, 0); 
    if (descSock == -1) 
    {   
        perror("Erreur Creation Socket RDV\n");
        exit(3);
    }   
    return (descSock);
}
