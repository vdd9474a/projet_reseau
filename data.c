#include "data.h"

int size;

typedef struct s_data
{
  char addr[17];
  char listeFichiers[256];
} t_data;


Data initData()
{
	Data info = malloc(sizeof(struct s_data));
	info->listeFichers = {0};
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
/*TODO: gerer l'ajout dans le tableau en rajoutant en ';' entre chaque nom de fichier*/
    if (info == NULL)
        Erreur("la structure en parametre n'est pas initialisée: ",98);
    if (fileName == NULL)
        Erreur("la chaine de charactere en parametre n'est pas initialisée: ",97);
        
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


void listFilesInDir(char * dir)
{
/*TODO: mettre les noms de fichier en parametre de addFileInListFiles*/
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;

    mydir = opendir(dir);
    while((myfile = readdir(mydir)) != NULL)
    {
        stat(myfile->d_name, &mystat);    
        printf(" %s\n", myfile->d_name);
    }
    closedir(mydir);
}






