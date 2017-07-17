#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int checkInput(int argc, char **argv, int *index){

	int i, j, res=0, c=0;
	
	for(i=1;i<argc;i++){

		if(argv[i][0] != '-'){

			if(c > 0) return -2;

			if(access(argv[i], F_OK)){

				return -2;

			} else {

				*index = i;

				c++;

				continue;

			}

		}



		for(j=1;argv[i][j] != '\0';j++){

			if(argv[i][j] == 'e' && ((res & 1) == 0)){

				res = res | 1;

			} else if(argv[i][j] == 'p' && ((res & 2) == 0)){

				res = res | 2;

			} else if(argv[i][j] == 's'&& ((res & 4) == 0)){

				res = res | 4;

			} else {

				return -1;

			}

		}

	}


	return res;

}



int main(int argc, char **argv){

	int res, index, i=0;
	char buffer[100], option[4];

	
	if(argc < 2){

		printf("input file name\n");

		return 0;

	} else{

		res = checkInput(argc, argv, &index);

		if(res == -1){

			printf("invalid option\n");

			return 0;

		}else if(res == -2){

			printf("invalid file name\n");

			return 0;

		}

	} 

	

	if(res == 0||((res & 1) == 1)) option[i++] = 'h';

	if((res & 2) == 2) option[i++] = 'l';

	if((res & 4) == 4) option[i++] = 'S';

	option[i] = '\0';



	sprintf(buffer, "readelf -%s %s", option, argv[index]);

	system(buffer);

	return 0;

}


