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

void swap(t_jogador *i, t_jogador *j) {
   t_jogador temp = *i;
   *i = *j;
   *j = temp;
}

void construir(t_jogador *subConjJogador, int tamHeap){
	for(int i = tamHeap; i > 1 && subConjJogador[i].altura > subConjJogador[i/2].altura; i /= 2){
		swap(subConjJogador + i, subConjJogador + i/2);
	}
}
//=============================================================================
int getMaiorFilho(t_jogador *subConjJogador, int i, int tamHeap){
	int filho;
	if (2*i == tamHeap || subConjJogador[2*i].altura > subConjJogador[2*i+1].altura){
		filho = 2*i;
	} else {
		filho = 2*i + 1;
	}
	return filho;
}
//=============================================================================
void reconstruir(t_jogador *subConjJogador, int tamHeap){
	int i = 1;
	while(i <= (tamHeap/2)){
		int filho = getMaiorFilho(subConjJogador, i, tamHeap);
		if(subConjJogador[i].altura < subConjJogador[filho].altura){
			swap(subConjJogador + i, subConjJogador + filho);
			i = filho;
		}else{
			i = tamHeap;
		}
	}
}
//=============================================================================
void heapsort(t_jogador *subConjJogador, int n) {
	//Alterar o vetor ignorando a posicao zero
	t_jogador arrayTmp[n+1];
	for(int i = 0; i < n; i++){
		arrayTmp[i+1] = subConjJogador[i];
	}

	//Contrucao do heap
	for(int tamHeap = 2; tamHeap <= n; tamHeap++){
		construir(arrayTmp, tamHeap);
	}

	//Ordenacao propriamente dita
	int tamHeap = n;
	while(tamHeap > 1){
		swap(arrayTmp + 1, arrayTmp + tamHeap--);
		reconstruir(arrayTmp, tamHeap);
	}

	//Alterar o vetor para voltar a posicao zero
	for(int i = 0; i < n; i++){
		subConjJogador[i] = arrayTmp[i+1];
	}
}

void fragmentSort(t_jogador *subConjJogador, int tam) {
	bool status = false;
	int i = 0;

	while(i <= tam-1) {
		for(int j = i+1; j <= tam; j++) {
			if(subConjJogador[i].altura == subConjJogador[j].altura) {
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
	t_jogador subConjJogador[463];

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

			if(atoi(idJogador) == jogador[i].id) {

				subConjJogador[j] = jogador[i];

				j++;

				break;
			}

		}
		// Informar o id do jogador
		scanf("%s",idJogador);
	}

	heapsort(subConjJogador, j-1);

	fragmentSort(subConjJogador, j-1);

	for(i = 0; i < 10; i++) {
		printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", subConjJogador[i].id, subConjJogador[i].nome, subConjJogador[i].altura, subConjJogador[i].peso, subConjJogador[i].anoNascimento, subConjJogador[i].universidade, subConjJogador[i].cidadeNascimento, subConjJogador[i].estadoNascimento);
	}

	return 0;
}
