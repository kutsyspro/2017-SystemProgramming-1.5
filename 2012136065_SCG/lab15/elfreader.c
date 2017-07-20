#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int elf_options(char* argv[]){
	int sum = 0;
	int i = 0;
	char ch = argv[1][i];
	
	if(ch != '-'){
		perror("Option Error : ");
		exit(0);
	}else{
		while(ch != '\0'){
			i++;
			ch = argv[1][i];
		
			if(ch == 'e'){
				sum += 1;
			}else if(ch == 'p'){
				sum += 10;
			}else if(ch == 's'){
				sum += 100;
			}
		}
	}
	return sum;
}

int main(int argc, char* argv[]){
	int options;
	char buffer[100];

	if(argc < 2){
		printf("Usage: readelf <option(s)> elf-file(s)\n");
		exit(0);
	}else if(argc == 2){
		sprintf(buffer, "%s", "readelf -h ");
		strcat(buffer, argv[1]);
		system(buffer);
	}else if(argc == 3){
		options = elf_options(argv);

		switch(options){
		case 1:
			sprintf(buffer, "%s", "readelf -h ");
			strcat(buffer, argv[2]);
			system(buffer);
			break;
		case 10:
                        sprintf(buffer, "%s", "readelf -l ");
                        strcat(buffer, argv[2]);
                        system(buffer);
			break;
		case 11:
                        sprintf(buffer, "%s", "readelf -hl ");
                        strcat(buffer, argv[2]);
                        system(buffer);
			break;
		case 100:
                        sprintf(buffer, "%s", "readelf -S ");
                        strcat(buffer, argv[2]);
                        system(buffer);
                        break;
		case 101:
                        sprintf(buffer, "%s", "readelf -hS ");
                        strcat(buffer, argv[2]);
                        system(buffer);
                        break;
		case 110:
                        sprintf(buffer, "%s", "readelf -lS ");
                        strcat(buffer, argv[2]);
                        system(buffer);
                        break;
		case 111:
                        sprintf(buffer, "%s", "readelf -hlS ");
                        strcat(buffer, argv[2]);
                        system(buffer);
                        break;
		}
	}else{
                printf("Usage : Program ELF_file or Program [-option] ELF_file\n");
                exit(0);
	}

	return 0;
}
