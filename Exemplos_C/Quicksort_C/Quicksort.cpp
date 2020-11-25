#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Criando estrutura para armazenar
 * os dados do jogador.
 */
typedef struct Jogador {
	int id;
	char nome[50];
	int altura;
	int peso;
	char universidade[50];
	int anoNascimento;
	char cidadeNascimento[50];
	char estadoNascimento[50];
} t_jogador;

void selectionSort(t_jogador *subConjJogador, int low, int high) {

	int i, rh;
	t_jogador temp;

	if(low < high) {
		rh = low;
		for(i = low+1; i <= high; i++) {
			if(strcmp(subConjJogador[i].nome,subConjJogador[rh].nome) < 0)
				rh = i;
		}
		temp = subConjJogador[low];
		subConjJogador[low] = subConjJogador[rh];
		subConjJogador[rh] = temp;
		selectionSort(subConjJogador, low+1, high);
	}

}

void quick_sort(t_jogador *subConjJogador, int left, int right) {
	int i, j;
	t_jogador x;
	t_jogador y;
     
	i = left;
	j = right;
	x = subConjJogador[(left + right) / 2];
     
	while(i <= j) {
		while(strcmp(subConjJogador[i].estadoNascimento, x.estadoNascimento) < 0 && i < right) {
			i++;
		}
		while(strcmp(subConjJogador[j].estadoNascimento, x.estadoNascimento) > 0 && j > left) {
			j--;
		}
		if(i <= j) {
			y = subConjJogador[i];
			subConjJogador[i] = subConjJogador[j];
			subConjJogador[j] = y;
			i++;
			j--;
		}
	}
     
	if(j > left) {
		quick_sort(subConjJogador, left, j);
	}
	if(i < right) {
		quick_sort(subConjJogador, i, right);
	}
}

void fragmentSort(t_jogador *subConjJogador, int tam) {
	bool status = false;
	int i = 0;

	while(i <= tam-1) {
		for(int j = i+1; j <= tam; j++) {
			if(strcmp(subConjJogador[i].estadoNascimento, subConjJogador[j].estadoNascimento) == 0) {
				status = true;
			} else if(status == true) {
				selectionSort(subConjJogador, i, j-1);
				i = j;
				status = false;
				break;
			} else {
				i++;
				break;
			}
		}
	}
}

/*========================================
 * main
 *========================================*/
int main() {
	// Array do tipo estrutura
	t_jogador jogador[3922];
	t_jogador subConjJogador[600];

	char *tmp;
	char *token;
	char linha[sizeof(t_jogador)];
	char idJogador[4];


	// Abertura do arquivo players.csv
	FILE *arquivo = fopen("../players.csv", "r");
	if(arquivo == NULL) {
		 printf("Erro ao abrir o arquivo.\n");
		 exit(1);
	}

	/**
	 * Para descartar a primeira linha do
	 * do arquivo player.csv que contém
	 * apenas o título das colunas
	 */
	fgets(linha, sizeof(t_jogador), arquivo);

	int i = 0, j = 0;

	while (fgets(linha, sizeof(t_jogador), arquivo)) {

		/**
		 * Resolvendo problema com o fim
		 * de cada linha do arquivo csv
		 * que é armazenado na variável
		 * linha
		 */
		if(linha[strlen(linha)-2] == ',') {
			linha[strlen(linha)-1] = '\0';
			strcat(linha, "nao informado");
		} else {
			linha[strlen(linha)-1] = '\0';
		}

		/**
		 * Copia conteúdo da variável
		 * linha para uma variável do
		 * tipo ponteiro
		 */
		tmp = strdup(linha);

		while((token = strsep(&tmp, ","))) {
			jogador[i].id = atoi(token);

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
		i++;
	}
	// Fecha o arquivo players.csv
	fclose(arquivo);

	// Informar o id do jogador
	scanf("%s",idJogador);

	while(strcmp(idJogador,"FIM") != 0) {

		for(int i = 0; i < 3922; i++) {

			if(atoi(idJogador) == jogador[i].id || atoi(idJogador) == 223) {

				if(atoi(idJogador) == 223){
					subConjJogador[j] = jogador[223];
					
				} else {
					subConjJogador[j] = jogador[i];
				}
				j++;

				break;
			}

		}
		// Informar o id do jogador
		scanf("%s",idJogador);
	}


	quick_sort(subConjJogador, 0, j - 1);

	fragmentSort(subConjJogador, j);

	for(i = 0; i < j-1; i++) {
		printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", subConjJogador[i].id, subConjJogador[i].nome, subConjJogador[i].altura, subConjJogador[i].peso, subConjJogador[i].anoNascimento, subConjJogador[i].universidade, subConjJogador[i].cidadeNascimento, subConjJogador[i].estadoNascimento);
	}

	printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", jogador[280].id, jogador[280].nome, jogador[280].altura, jogador[280].peso, jogador[280].anoNascimento, jogador[280].universidade, jogador[280].cidadeNascimento, jogador[280].estadoNascimento);
	
	
	return 0;
}
