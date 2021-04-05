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

int tiraDigito (char *v, char letra, int tam)
{
	int i = 0, j;

	for (j = 0; j <= tam; ++j){
		if (v[j] != letra) v[i++] = v[j];
	}
	i -= 1;
	return i;
}

int substituirDigito (char *v, char letra, int tam)
{
	int i = 0, j;

	for (j = 0; j <= tam; ++j){
		if (v[j] == letra) v[j] = ';';
	}
	i -= 1;
	return i;
}

int tiraNuloEsquerda (char *v, int tam)
{
	int i, j = 0;

	while(v[j] == '0') {
		j++;
	}
	for (i = 0; i < tam; ++i)
	{
		v[i] = v[j];
		j++;
	}
	return i;
}

void inverterString(char *strg)
{
	int w, number;
	int temp = 0;

	for(number=0; strg[number] != 0; number++);
	for(w = 0; w <number/2; w++)
	{
		temp = strg[w];
		strg[w]=strg[number - 1 - w];
		strg[number - 1 - w] = temp;
	}
}

int main() {

	char linha[50];

	char **res = NULL;
	int count = 0;
	int rc;

	/*Scanf ler string com espaço -> Exemplo
		scanf("%[^\n]", linha); scanf("%*c"); *Segundo scanf limpa o buffer*
	*/

	for (int i = 0; i < 2; ++i) {
		input(linha, sizeof(linha));

		/*Removendo digito da String -> Exemplo
			tiraDigito(linha, ',', strlen(linha));
			printf("%s\n", linha);*/

		/*Substituir um digito por outro na String -> Exemplo
			 substituirDigito(linha, ',', strlen(linha));
			 printf("%s\n", linha);*/

		/*String invertida -> Exemplo
			inverterString(linha);
			printf("%s\n", linha);*/

		rc = split( linha, " ", &res, &count );

		if( rc ) {
			printf("Error: %s errno: %d \n", strerror(errno), errno);
		}

		/*Removendo zeros a esquerda -> Exemplo
			tiraNuloEsquerda(res[0], strlen(res[0]));
			printf("%s\n", res[0]);*/

		for (int i = 0; i < count; i++)
			printf("%d - %s\n", i, res[i]);

		free(res);
	}

	return 0;
}
