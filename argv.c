#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "find.c"
void getSubDirect(char * dirName,int fielCheck,int dirChecek);
int main(int argc, char const *argv[])
{
	//if(strcmp(argv[3],"-d"))
	//{
  printf("%s\n", argv[4]);
  int dirSize = getDirSize (argv[4]); //gets number of different directories
  char** dr = (char **) malloc (sizeof (char *) * dirSize); //Array of directories 
  getDir(dr,argv[4],dirSize); // function that gets the array of directories

	DIR *directory;
    struct dirent *dp;
 char** dir = (char **) malloc (sizeof (char *) * 255);
  getSubDirect(*dr,0,16);
	return 0;
}
int checkName(char *needCheck)
{
  int size = strlen(needCheck);
  char * csv = (char*) malloc(sizeof(char*)*4);
  sprintf(csv,"%s",needCheck+size-4);
  return strcmp(csv,".csv");
}
void getSubDirect(char * dirName,int fileCheck,int dirCheck)
{ 
  DIR *directory;
    struct dirent *dp;
    printf("%s\n",dirName );
    if ((directory = opendir (dirName)) == NULL) {
        perror ("Cannot open .");
        exit (1);
    }


   while ((dp = readdir(directory)) != NULL) {
            //printf ("%d: %s\n", dp->d_type,dp->d_name);
            if(dp->d_type == dirCheck && strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") !=0 )
            { 
             // system("PAUSE");
              char * new_str ;
                  if((new_str = (char*) malloc(strlen(dirName)+strlen(dp->d_name)+2)) != NULL){
                    
                    new_str[0] = '\0';   // ensures the memory is an empty string
                      strcat(new_str,dirName);
                      strcat(new_str,"\\");
                      strcat(new_str,dp->d_name);
                  getSubDirect(new_str,fileCheck,dirCheck);
                  }
              }
              else if(dp->d_type == fileCheck)
              {
                if(checkName(dp->d_name) == 0)
                {
                char * new_str ;
                  if((new_str = (char*) malloc(strlen(dirName)+strlen(dp->d_name)+1)) != NULL){
                    new_str[0] = '\0';   // ensures the memory is an empty string
                      strcat(new_str,dirName);
                      strcat(new_str,dp->d_name);
              } else {
                fprintf(stdout,"malloc failed!\n");
              }
              printf ("%d: %s\n", dp->d_type,new_str);
            }
          } 
        }
        closedir (directory);
}
//C:\\MinGw\bin\argv.exe stuff hi -d D1