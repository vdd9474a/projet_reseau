#include "data.h"

#define TAILLEBLOCK 256

int size;

typedef struct s_data
{
  char addr[17];
  char listeFichiers[TAILLEBLOCK];
} t_data;


Data initData()
{
	Data info = (t_data *)malloc(sizeof(struct s_data));
	info->listeFichiers[0] = '\0';
	return info;
}

void deleteData(Data data)
{
  free(data);
}

void fileList(Data data)
{
   if (data == NULL)
        Erreur("la structure en parametre n'est pas initialisée: ",98);
   printf("%s \n", data->listeFichiers);
}

void addFileInListFile(char * fileName, Data info)
{
  int i=0;
  int sizeFileName = strlen(fileName);
  if (info == NULL)
    Erreur("la structure en parametre n'est pas initialisée: ",98);
  if (fileName == NULL)
        Erreur("la chaine de charactere en parametre n'est pas initialisée: ",97);
  while(i<255 || info->listeFichiers[i] == '\0')
  {
    i++;  
  }
  /*separation des noms de fichier par le caractere ';' */
  info->listeFichiers[i] = ';';
  if(255-(i++)>=(sizeFileName+1))
    strcpy(info->listeFichiers,fileName);    
}

void addAddress(Data info, char * addressRecieved)
{   
    if (info == NULL)
        Erreur("la structure en parametre n'est pas initialisée: ",98);
    if ( addressRecieved == NULL)
        Erreur("la chaine de charactere en parametre n'est pas initialisée: ",97);
  strcpy(info->addr,addressRecieved);
}

void initAddressTable(char ** table)
{
  int i;
  table = malloc(sizeof *table * 2);
  
  for (i = 0; i < 2; i++)
  {
    table[i] = malloc(sizeof **table * 17);
    
  }
  size = 0;
}

void deleteAddessTable( char ** table)
{
  int i;
  
  for(i = 0; i < size; i++)
  {
    free(table[i]);  
  }
  size =0;
  free(table);
}

void addAddressInTable(char ** table, char * address)
{
  if (table == NULL )
     Erreur("la structure en parametre n'est pas initialisée: ",98);
  if (size>=2 )
  {
     char **tmp = realloc(table,sizeof *table);
     if (tmp == NULL)
    {
       free(tmp);
       Erreur("erreur lors de l'allocation de mémoire: ",96);
    }
    else
       table = tmp;
       table[size] = malloc(sizeof **table * 17);  
  }
  table[size]= address;    
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
	/*on compte le nombre de caractere + 2 qui correspond au caractere null non-compte avec strlen 
	 * et le ';' qu'il faudra rajouter dans notre structure data
	 */
        sizeOct+= strlen(myfile->d_name)+2;
    }
    closedir(mydir);
    
    return sizeOct;
}






