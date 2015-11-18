#include "erreur.h"


void Erreur(char* mess, int code)
{
 	perror(mess);
 	exit(code);
}
