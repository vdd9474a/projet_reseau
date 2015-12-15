#include "data.h"

#define TAILLEBLOCK 256

int size;

typedef struct s_data
{
  char addr[17];
  char listeFichiers[TAILLEBLOCK];
  int nombreFichier;
} t_data;


Data initData()
{
	Data info = (t_data *)malloc(sizeof(struct s_data));
	info->listeFichiers[0] = '\0';
	info->nombreFichier = 0;
	return info;
}

void deleteData(Data data)
{
  free(data);
}

void fileList(Data data)
{
   if (data == NULL)
        erreur("la structure en parametre n'est pas initialisée: ",98);
   printf("%s \n", data->listeFichiers);
}

void addFileInListFile(char * fileName, Data info)
{
  int i=0;
  int j;
  int sizeFileName = strlen(fileName)+1;
 
  if (info == NULL)
    erreur("la structure en parametre n'est pas initialisée: ",98);
  if (fileName == NULL)
    erreur("la chaine de charactere en parametre n'est pas initialisée: ",97);
  
  while(i<255 && info->listeFichiers[i] != '\0')
  {
    i++;  
  }
  /*printf("%d\n",i);*/
  /*separation des noms de fichier par le caractere ';' */
  if(i!=0)
    info->listeFichiers[i++] = ';';/**/
    
  if(255-(i+1)>=(sizeFileName))
    for(j=0;j<sizeFileName;j++)
    {
      info->listeFichiers[i+j] = fileName[j];
    }
    
}

void addAddress(Data info, char * addressRecieved)
{   
    if (info == NULL)
        erreur("la structure en parametre n'est pas initialisée: ",98);
    if ( addressRecieved == NULL)
        erreur("la chaine de charactere en parametre n'est pas initialisée: ",97);
  strcpy(info->addr,addressRecieved);
}

/* Intialisation d'un tableau de chaine de caractere (adresse IP)
 * renvoie un tableau de chaine de caractere
 */
char** initAddressTable()
{
  int i;
  char ** table;
  /* allocation de la memoir pour le tableau a 2 dimension*/
  table = (char **)malloc(2* sizeof (*table));
  
  if(table == NULL)
    erreur("Erreur d'alocation du tableau d'adresse IP: ",96);
  
  for (i = 0; i < 2; i++)
  {
    /*alocation de la memoir pour le tableau de caractere*/
    table[i] = (char *)malloc(17* sizeof (**table));
    if(table[i] == NULL)
    {
      for(i=i-1;i>=0;i--)
	free(table[i]);
      free(table);
      erreur("Erreur d'alocation du tableau d'adresse IP: ",96);
    }
    
  }
  size = 0;
  return table;
}

void deleteAddessTable( char ** table)
{
  int i;
  if(size == 0)
  {
    for(i = 0; i < 2; i++)
    {
      free(table[i]);  
      
    }
  }
  else
    for(i = 0; i < 2; i++)
    {
      free(table[i]);  
      
    }
  size =0;
  free(table);
}

void addAddressInTable(char ** table, char * address)
{
  if (table == NULL )
     erreur("la structure en parametre n'est pas initialisée: ",98);
  if (size>=2 )
  {
    /* reallocation de la memoir afin de rajouter une case dans le tableau d'adresse IP(chaine de caractere)*/
     char **tmp = (char **)realloc(table,1*sizeof (*table));
     if (tmp == NULL)
    {
       free(table);
       erreur("erreur lors de l'allocation de mémoire: ",96);
    }
    else
       table = tmp;
       /* allocation de la memoir pour l'adresse IP (chaine de caractere)*/
       table[size] = (char *)malloc(17* sizeof (**table));  
  }
  strcpy(table[size],address);    
  size++;     
}


int listFilesInDir(char * dir)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    int sizeOct;

    mydir = opendir(dir);
    while((myfile = readdir(mydir)) != NULL)
    {
        stat(myfile->d_name, &mystat);
	/*on ne compte pas les dossiers caches*/
	while(myfile->d_name[0]=='.')
	  (myfile = readdir(mydir));
	/********************************************************************/
	/*                                                                  */
	/*	      fait pour le test                                     */
	/*                                                                  */
	/*	      printf("%s\n",myfile->d_name);                        */
	/********************************************************************/
	/*on compte le nombre de caractere + 2 qui correspond au caractere null non-compte avec strlen 
	 * et le ';' qu'il faudra rajouter dans notre structure data
	 */
        sizeOct+= strlen(myfile->d_name)+2;
    }
    closedir(mydir);
    
    return sizeOct;
}






