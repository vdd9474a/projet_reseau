/* http://broux.developpez.com/articles/c/sockets/ */

#include "fonc_sock.h"

int main (void)
{
	int comm = deploiement_serveur();
	ecrit_socket(comm, "coucou");
	close_connexion(comm);
}
