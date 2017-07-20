#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define _MAX_PATH 260

void printdir(char *dir, int depth){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL){
		fprintf(stderr, "cannot open directory:%s\n", dir);
		return;
	}

	chdir(dir);

	while((entry = readdir(dp)) != NULL){
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			/*Found a directory, but ignore. and...*/
			if(strcmp(".", entry->d_name) == 0 ||
			   strcmp("..", entry->d_name) == 0) continue;

			printf("%*s%s/\n", depth, "", entry->d_name);
			/*Reculse at a new indent level*/
			printdir(entry->d_name, depth+4);
		}else{
			if(!strncmp(".", entry->d_name, 1)) continue;
			else printf("%*s%s\n", depth, "", entry->d_name);
		}
	}
	chdir("..");
	closedir(dp);
}

int main(void){
	char strBuffer[_MAX_PATH] = {0};
	char *pstrBuffer = NULL;

	pstrBuffer = getcwd(strBuffer, _MAX_PATH);

	printf("Directory scan of %s:\n", pstrBuffer);
	printdir(pstrBuffer, 0);
	//printdir("/home", 0);
	printf("done.\n");
	exit(0);
}
