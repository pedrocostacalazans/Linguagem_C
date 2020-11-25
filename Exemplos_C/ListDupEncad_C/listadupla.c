#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define bool   short
#define true   1
#define false  0

//TIPO CELULA ===================================================================
typedef struct CelulaDupla {
	int id;
	char nome[50];
	int altura;
	int peso;
	char universidade[50];
	int anoNascimento;
	char cidadeNascimento[50];
	char estadoNascimento[50];       // Elementos inseridos na celula.
	struct CelulaDupla* prox; // Aponta a celula prox.
	struct CelulaDupla* ant;  // Aponta a celula anterior.
} CelulaDupla;

CelulaDupla* novaCelulaDupla(int id, char nome[50], int altura, int peso, int anoNascimento, char universidade[50], char cidadeNascimento[50], char estadoNascimento[50]) {
	CelulaDupla* nova = (CelulaDupla*) malloc(sizeof(CelulaDupla));
	nova->id = id;
	strcpy(nova->nome,nome);
	nova->altura = altura;
	nova->peso = peso;
	strcpy(nova->universidade, universidade);
	nova->anoNascimento = anoNascimento;
	strcpy(nova->cidadeNascimento, cidadeNascimento);
	strcpy(nova->estadoNascimento, estadoNascimento);
	nova->ant = nova->prox = NULL;
	return nova;
}

//LISTA PROPRIAMENTE DITA =======================================================
CelulaDupla* primeiro;
CelulaDupla* ultimo;


/**
 * Cria uma lista dupla sem elementos (somente no cabeca).
 */
void start () {
	primeiro = novaCelulaDupla(-1, " ", -1, -1, -1, " ", " ", " ");
	ultimo = primeiro;
}


/**
 * Insere um elemento na primeira posicao da lista.
 * @param x int elemento a ser inserido.
 */
/*
void inserirInicio(CelulaDupla *subConjJogador) {
	CelulaDupla* tmp = novaCelulaDupla(subConjJogador[0].id, );

	tmp->ant = primeiro;
	tmp->prox = primeiro->prox;
	primeiro->prox = tmp;
	if (primeiro == ultimo) {
		ultimo = tmp;
	} else {
		tmp->prox->ant = tmp;
	}
	tmp = NULL;
}
*/

/**
 * Insere um elemento na ultima posicao da lista.
 * @param x int elemento a ser inserido.
 */
void inserirFim(CelulaDupla *subConjJogador, int j) {
 	for (int i = 0; i < j; ++i) {
		ultimo->prox = novaCelulaDupla(subConjJogador[i].id, subConjJogador[i].nome, subConjJogador[i].altura, subConjJogador[i].peso, subConjJogador[i].anoNascimento, subConjJogador[i].universidade, subConjJogador[i].cidadeNascimento, subConjJogador[i].estadoNascimento);
		ultimo->prox->ant = ultimo;
		ultimo = ultimo->prox;
	}
}


/**
 * Remove um elemento da primeira posicao da lista.
 * @return resp int elemento a ser removido.
 */
/*
int removerInicio() {
	if (primeiro == ultimo) {
		errx(1, "Erro ao remover (vazia)!");
	}

	CelulaDupla* tmp = primeiro;
	primeiro = primeiro->prox;
	int resp = primeiro->elemento;
	tmp->prox = primeiro->ant = NULL;
	free(tmp);
	tmp = NULL;
	return resp;
}
*/

/**
 * Remove um elemento da ultima posicao da lista.
 * @return resp int elemento a ser removido.
 */
/*
int removerFim() {
	if (primeiro == ultimo) {
		errx(1, "Erro ao remover (vazia)!");
	}
	int resp = ultimo->elemento;
	ultimo = ultimo->ant;
	ultimo->prox->ant = NULL;
	free(ultimo->prox);
	ultimo->prox = NULL;
	return resp;
}
*/

/**
 *  Calcula e retorna o tamanho, em numero de elementos, da lista.
 *  @return resp int tamanho
 */
int tamanho() {
	int tamanho = 0;
	CelulaDupla* i;
	for(i = primeiro; i != ultimo; i = i->prox, tamanho++);
	return tamanho;
}


/**
 * Insere um elemento em uma posicao especifica considerando que o
 * primeiro elemento valido esta na posicao 0.
 * @param x int elemento a ser inserido.
 * @param pos int posicao da insercao.
 * @throws Exception Se <code>posicao</code> invalida.
 */
/*
void inserir(int x, int pos) {

	int tam = tamanho();

	if(pos < 0 || pos > tam){
		errx(1, "Erro ao remover (posicao %d/%d invalida!", pos, tam);
	} else if (pos == 0){
		inserirInicio(x);
	} else if (pos == tam){
		inserirFim(x);
	} else {
		// Caminhar ate a posicao anterior a insercao
		CelulaDupla* i = primeiro;
		int j;
		for(j = 0; j < pos; j++, i = i->prox);

		CelulaDupla* tmp = novaCelulaDupla(x);
		tmp->ant = i;
		tmp->prox = i->prox;
		tmp->ant->prox = tmp->prox->ant = tmp;
		tmp = i = NULL;
	}
}
*/

/**
 * Remove um elemento de uma posicao especifica da lista
 * considerando que o primeiro elemento valido esta na posicao 0.
 * @param posicao Meio da remocao.
 * @return resp int elemento a ser removido.
 * @throws Exception Se <code>posicao</code> invalida.
 */
/*
int remover(int pos) {
	int resp;
	int tam = tamanho();

	if (primeiro == ultimo){
		errx(1, "Erro ao remover (vazia)!");
	} else if(pos < 0 || pos >= tam){
		errx(1, "Erro ao remover (posicao %d/%d invalida!", pos, tam);
	} else if (pos == 0){
		resp = removerInicio();
	} else if (pos == tam - 1){
		resp = removerFim();
	} else {
		// Caminhar ate a posicao anterior a insercao
		CelulaDupla* i = primeiro->prox;
		int j;
		for(j = 0; j < pos; j++, i = i->prox);

		i->ant->prox = i->prox;
		i->prox->ant = i->ant;
		resp = i->elemento;
		i->prox = i->ant = NULL;
		free(i);
		i = NULL;
	}

	return resp;
}
*/

/**
 * Mostra os elementos da lista separados por espacos.
 */
void mostrar() {
	CelulaDupla* i;
	for (i = primeiro->prox; i != NULL; i = i->prox) {
		printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", i->id, i->nome, i->altura, i->peso, i->anoNascimento, i->universidade, i->cidadeNascimento, i->estadoNascimento);
	}
}


/**
 * Mostra os elementos da lista de forma invertida
 * e separados por espacos.
 */
void mostrarInverso() {
	printf("[ ");
	CelulaDupla* i;
	for (i = ultimo; i != primeiro; i = i->ant){
		printf("%d ", i->id);
	}
	printf("] \n"); // Termina de mostrar.
}


/**
 * Procura um elemento e retorna se ele existe.
 * @param x Elemento a pesquisar.
 * @return <code>true</code> se o elemento existir,
 * <code>false</code> em caso contrario.
 */
/*
bool pesquisar(int x) {
	bool resp = false;
	CelulaDupla* i;

	for (i = primeiro->prox; i != NULL; i = i->prox) {
		if(i->elemento == x){
			resp = true;
			i = ultimo;
		}
	}
	return resp;
}
*/

void quick_sort(CelulaDupla *subConjJogador, int left, int right) {
	int i, j;
	CelulaDupla x;
	CelulaDupla y;

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


void selectionSort(CelulaDupla *subConjJogador, int low, int high) {

	int i, rh;
	CelulaDupla temp;

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


void fragmentSort(CelulaDupla *subConjJogador, int tam) {
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
				i = tam;
				break;
			}
		}
	}
}


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


int main() {
	// Array do tipo estrutura
	CelulaDupla jogador[3922];
	CelulaDupla subConjJogador[463];

	char *tmp;
	char *token;
	char linha[sizeof(CelulaDupla)];
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
	fgets(linha, sizeof(CelulaDupla), arquivo);

	int i = 0, j = 0;

	while (fgets(linha, sizeof(CelulaDupla), arquivo)) {

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

				printf("%s\n", subConjJogador[j].estadoNascimento);

				j++;

				break;
			}

		}
		// Informar o id do jogador
		scanf("%s",idJogador);
	}

	quick_sort(subConjJogador, 0, j-1);

	fragmentSort(subConjJogador, j);

	start();

	inserirFim(subConjJogador, j);

	mostrar();


	return 0;
}
