#ifndef IOFICHIER_H
#define IOFICHIER_H

#define LECTURE O_RDONLY
#define ECRITURE O_WRONLY|O_CREAT

#include <fcntl.h>

/* Structure Bloc
 * Permet de stoque les info d'un fichier (lecture ou ecriture)
 */
typedef struct s_bloc * Bloc;

/* Fonction qui modifie la taille d'un bloc (256 par defaut)
 */
void set_tailleBloc(int taille);

/* Fonction qui retourne la taille d'un bloc (256 par defaut)
 */
int get_tailleBloc();

/* Fonction qui creer un Bloc de la taille défini par set_tailleBloc(int) ou par 256 octets (defaut)
 * Retourne un Bloc
 */
Bloc creer_bloc();

/* Fonction qui détruit un Bloc
 */
void supprimer_bloc(Bloc bloc);

/* Fonction qui ouvre un fichier sur le disque dure
 * 	mode : LECTURE | ECRITURE
 * Retourne descripteur fichier
 */
int ouvrirFichier(char * nomF, int mode);

/* Fonction qui creer un fichier (ecriture seulement)
 * retourne descripteur fichier
 */
int creerFichier(char * nomF);

/* Fonction qui ferme le fichier dont le descripteur est passe par parametre
 */
void fermerFichier(int desc);

/* Procedure qui remplis le Bloc de données du fichier spécifie 
 * 	Pour les fichier ouvert en mode LECTURE
 * 	Retourne la taille lu
 */
int lire_blocFichier(int desc, Bloc bloc);

/* Fonction qui écrit dans le fichier specifié, le contenu du bloc
 * 	Pour les fichier ouverts en ECRITURE
 */
void ecrire_blocFichier(int desc, Bloc bloc);

#endif
