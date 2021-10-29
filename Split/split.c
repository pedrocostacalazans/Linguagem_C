/*
	Autor: Pedro Costa Calazans
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Atua como se fosse a fgets sendo chamada com o fluxo da entrada padrão, stdin,
   mas não inclui a nova linha na string */
char* input(char* string, int tamanho) {
	if(fgets(string, tamanho, stdin) != NULL) {
		/* Remove a nova linha (\n), caso ela tenha sido lida pelo fgets */
		int indiceUltimoCaractere = strlen(string) - 1;

		if(string[indiceUltimoCaractere] == '\n') {
			string[indiceUltimoCaractere] = '\0';
		}
		
		return string;
	}

	return NULL;
}

int split(char *str, const char *delim, char ***array, int *length) {
	int i=0;
	char *token;
	char **res = (char **) malloc(0 * sizeof(char *));
	if( !res ) return -1;

  /* get the first token */
	token = strtok(str, delim);
	while( token != NULL ) {
		res = (char **) realloc(res, (i + 1) * sizeof(char *));
		if( !res ) return -1;
		res[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	*array = res;
	*length = i;
	return 0;
}

int main() {

	char linha[50];

	char **res = NULL;
	int count = 0;
	int rc;

	input(linha, sizeof(linha));

	while(strcmp(linha, "FIM") != 0) {
		input(linha, sizeof(linha));
	}

	input(linha, sizeof(linha));

	for (int i = 0; i < 32; ++i) {
		input(linha, sizeof(linha));

		rc = split( linha, " ", &res, &count );

		if( rc ) {
			printf("Error: %s errno: %d \n", strerror(errno), errno);
		}

		for (int i = 0; i < count; i++)
			printf("%d - %s\n", i, res[i]);

		free(res);
	}

	return 0;
}
