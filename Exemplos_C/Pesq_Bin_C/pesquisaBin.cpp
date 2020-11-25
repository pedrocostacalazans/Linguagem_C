#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE_STRING 50
#define TAMANHO 100

/**
 * MergeSort
 */
//=============================================================================
void intercalar(int* array, int esq, int meio, int dir){
   int n1, n2, i, j, k;

   //Definir tamanho dos dois subarrays
   n1 = meio-esq+1;
   n2 = dir - meio;

   int* a1 = (int*) malloc((n1+1) * sizeof(int)); 
   int* a2 = (int*) malloc((n2+1) * sizeof(int));

   //Inicializar primeiro subarray
   for(i = 0; i < n1; i++){
      a1[i] = array[esq+i];
   }

   //Inicializar segundo subarray
   for(j = 0; j < n2; j++){
      a2[j] = array[meio+j+1];
   }

   //Sentinela no final dos dois arrays
   a1[i] = a2[j] = 0x7FFFFFFF;

   //Intercalacao propriamente dita
   for(i = j = 0, k = esq; k <= dir; k++){
      array[k] = (a1[i] <= a2[j]) ? a1[i++] : a2[j++];
   }
}
//=============================================================================
void mergesortRec(int *array, int esq, int dir){
   if (esq < dir){
      int meio = (esq + dir) / 2;
      mergesortRec(array, esq, meio);
      mergesortRec(array, meio + 1, dir);
      intercalar(array, esq, meio, dir);
   }
}
//=============================================================================
void mergesort(int *array, int n) {
   mergesortRec(array, 0, n-1);
}
//=============================================================================

typedef struct Jogador {
	int id;
	char nome[SIZE_STRING];
	int altura;
	int peso;
	char universidade[SIZE_STRING];
	int anoNascimento;
	char cidadeNascimento[SIZE_STRING];
	char estadoNascimento[SIZE_STRING];
} t_jogador;


/**
 * Busca recursivamente o item dentro do vetor vector. A cada iteração
 * reduz o espaço de busca pela metade. Quando encontra o item retorna
 * o índice onde ele foi encontrado. Caso contrário retorna -1
 */
 
bool pesqBin(int *ids, int id) {
	int direita, esquerda, meio;
	bool encontrado = 0; /*Falso*/
	esquerda = 0;
	direita = TAMANHO - 1;

	while(esquerda<=direita && !encontrado){
		meio=(direita+esquerda)/2;
		if (ids[meio] == id)
			encontrado = 1; /*Verdadeiro*/
		else if (id < ids[meio])
			direita = meio - 1;
		else
			esquerda = meio + 1;
	}
	return encontrado;
}

bool buscaId(int *ids, int id) {
	bool ret = false;
	for(int x=0; x < 50; x++) {
		if(ids[x] == id) {
			ret = true;
			break;
		}
	}
	return ret;
}

void tratarFgets(char *string) {
	for(int i = SIZE_STRING; i > 0; i--) {
		if( string[i] == '\n') {
			string[i] = '\0';
			break;
		}
	}
}

/**
 * Método main
 */
int main() {

	t_jogador jogador[3922];
	
	int i = 0;
	int ids[100];

	char string[SIZE_STRING];
	char *token;
	char *tmp;
	char linha[sizeof(t_jogador)];
	bool status=false;

	FILE *arquivo = fopen("../players.csv", "r");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fgets(linha, sizeof(t_jogador), arquivo);

	while (fgets(linha, sizeof(t_jogador), arquivo)) {

		if(linha[strlen(linha)-2] == ',') {
			linha[strlen(linha)-1] = '\0';
			strcat(linha, "nao informado");
		} else {
			linha[strlen(linha)-1] = '\0';
		}

		tmp = strdup(linha);

		while((token = strsep(&tmp, ","))) {
			i = atoi(token);
			jogador[i].id = i;

			token = strsep(&tmp, ",");
			strcpy(jogador[i].nome, token);

			token = strsep(&tmp, ",");
			jogador[i].altura = atoi(token);

			token = strsep(&tmp, ",");
			jogador[i].peso = atoi(token);

			token = strsep(&tmp, ",");
			strcmp(token, "") == 0 ? strcpy(jogador[i].universidade, "nao informado") : strcpy(jogador[i].universidade, token);

			token = strsep(&tmp, ",");
			jogador[i].anoNascimento = atoi(token);

			token = strsep(&tmp, ",");
			strcmp(token, "") == 0 ? strcpy(jogador[i].cidadeNascimento, "nao informado") : strcpy(jogador[i].cidadeNascimento, token);

			token = strsep(&tmp, ",");
			strcpy(jogador[i].estadoNascimento, token);
		}
	}

	fclose(arquivo);

	i = 0;
	
	fgets(string, SIZE_STRING, stdin);
	tratarFgets(string);
	
	while(strcmp(string, "FIM") != 0) {
				
		ids[i] = atoi(string);
		i++;

		fgets(string, SIZE_STRING, stdin);
		tratarFgets(string);
	}

	mergesort(ids, 100);

	fgets(string, SIZE_STRING, stdin);
	tratarFgets(string);

	while(strcmp(string, "FIM") != 0) {
		
		for(i = 0; i < 3922; i++) {
			if(strcmp(string, jogador[i].nome) == 0) {
				if(pesqBin(ids, jogador[i].id)) {
					printf("SIM\n");
					status = true;
					break;
				}				
			}
		}
		
		if(status == false) {
			printf("NAO\n");
		} else status = false;

		fgets(string, SIZE_STRING, stdin);
		tratarFgets(string);
	}

	return(0);
}
