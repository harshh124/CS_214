#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int csv_line_count(FILE *fp);
char *strip(char * input);

char *strip(char * input) {

	char *end = input + strlen(input);

	while (end > input && *end != '.') {
		--end;
	}

	if (end > input) {
		*end = '\0';
	}
	//printf("output input (in fun)file name: %s\n",input);
	//printf("output end (in fun)file name: %s\n",end);

	return input;
}

int csv_line_count(FILE *fp) {
	int count;

		char *line = NULL;								// pointer for each line
		size_t len = 0;
		ssize_t read;
		int ctotal = 1;						// count the total number of tokens

		//this while loop will break each line into tokens
		while ((read = getline(&line, &len, fp)) != -1) {
			char *p;
			count = 1;
			while ((p = strsep(&line, ",")) != NULL) {
			}
			ctotal++;
		}
		//printf("Ctotal = %d\n", ctotal);



	// Close the file
	fclose(fp);
	return ctotal;
}
void print(const char *name, const char *output);

void print(const char * name, const char *output) {

	printf("Inputs: %s and %s\n", name, output);

	DIR *dir;
	FILE *fp;
	int counter;
	struct dirent *entry;
	char * wDir = (char *) malloc(sizeof(char) * 20); //save a copy of the working dir

	if (!(dir = opendir(name)))
		return;

	while ((entry = readdir(dir)) != NULL) {

		if (entry->d_type == DT_DIR) {
			char path[1024];
			if (strcmp(entry->d_name, ".") == 0
					|| strcmp(entry->d_name, "..") == 0) {
				continue;
			}

			char cwd[256];
			if (getcwd(cwd, sizeof(cwd)) == NULL)
				perror("getcwd() error");
			else
				printf("current working directory2 is: %s\n", cwd);

			printf("%s\n", entry->d_name);
			strcpy(wDir, entry->d_name);

			print(entry->d_name, output);
		} else {
			char *point = entry->d_name;
			if ((point = strrchr(point, '.')) != NULL) {
				if (strcmp(point, ".csv") == 0) {
					//ends with csv
					printf("%s\n", entry->d_name);

					//change the working directory
					//chdir(name);

					//get working dir
					char cwd[256];
					if (getcwd(cwd, sizeof(cwd)) == NULL)
						perror("getcwd() error");
					else
						printf("current working directory3 is: %s\n", cwd);

					//opening file
					//
					char * new_str ;
					if((new_str = (char*) malloc(strlen(wDir)+strlen(entry->d_name)+1)) != NULL){
   					 new_str[0] = '\0';   // ensures the memory is an empty string
   					 strcat(new_str,wDir);
    				 strcat(new_str,entry->d_name);
					} else {
    					fprintf(stdout,"malloc failed!\n");
						}
					fp = fopen(new_str, "r");
					if (fp == NULL) {
						printf("Could not open file %s\n", entry->d_name);
						exit(0);
					}
					//printf("The output name is %s\n",output);
					/*counter = csv_line_count(fp);
					printf("The file %s has %d lines\n ", entry->d_name,
							counter);*/
					//fclose(fp);
				}
			}

		}
	}    //end while
	closedir(dir);

}

int main(int argc, char* argv[]) {

	/*printf("number of args = %d\n", argc);
	 int i = 0;
	 for (i; i < argc; i++) {
	 printf("argc[%d] = %s\n", i, argv[i]);
	 }*/

	if (argc <= 2) {
		printf("Error. Not enough arguments provided.\n");
		exit(1);
	}
// getting the "-c" field
	char * sF = (char *) malloc(sizeof(char) * 25); //sF = sortingField. The arg after "-c"
	strcpy(sF, argv[2]);
	//printf("sF = %s\n", sF);

// checking for "-d"
	char * wDir = (char *) malloc(sizeof(char) * 20);
	char * oDir = (char *) malloc(sizeof(char) * 20);
	strcpy(wDir, ".");
	strcpy(oDir, ".");
	//printf("The wDir name is %s\n",wDir);
	//printf("The oDir name is %s\n",oDir);
	//DIR *wDir = opendir("."); 	// workingDirectory
	//DIR *oDir = opendir(".");   // outputDirectory

	if (argc > 4) {
		if (!(strcmp("-d", argv[3]))) { 	// working directory was given
			//wDir = opendir(argv[4]);

			// opening the directory given
			strcpy(wDir, argv[4]);
			//printf("opened %s\n", argv[4]);
		} else if (!(strcmp("-o", argv[3]))) {
			//oDir = opendir(argv[4]);
			// saving the directory given
			strcpy(oDir, argv[4]);
			//printf("saved %s\n", argv[4]);
		}
	}
// checking for "-o"
	if (argc > 5) {
		if (!(strcmp("-o", argv[5]))) {
			//oDir = opendir(argv[6]);
			// opening the directory given
			strcpy(oDir, argv[6]);
			//printf("saved 2 %s\n", argv[6]);
		}
	}

	print(wDir, oDir);

	return 0;

}