/*
 =====================================
 Name        : cpp.c
 Author      : Alan Calazans
 Version     :
 Copyright   : Your copyright notice
 Description : Compilador C++
 =====================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_CMD 300
#define SIZE_AUX 200

void nomeSemExt(char *name);

int main(int argc, const char *argv[]) {
	char cmd[SIZE_CMD],
		   aux[SIZE_AUX];

	strcpy(aux, argv[1]);

	nomeSemExt(aux);

	if(argc > 2) {
		for(int i = 2; i < argc; i++) {
			strcat(aux, " ");
			strcat(aux, argv[i]);
		}
	}

#ifdef WIN
	sprintf(cmd, "g++ -Wall -C %s -o %s", argv[1], aux);
	system("cls");
#else
  #ifdef NIX
    sprintf(cmd, "g++ -Wall -C %s -o %s", argv[1], aux);
    system("clear");
  #else
    #error Especificar -DWIN ou -DNIX na compilacao!
  #endif
#endif

	printf("%s\n", cmd);
	system(cmd);

	return 0;
}

void nomeSemExt(char *aux) {
	for (int i = 0; i < SIZE_AUX; i++) {
		if(aux[i] == '.') {
			aux[i] = '\0';
			break;
		}
	}
}
