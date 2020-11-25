#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TipoChave;
typedef char Tipochave[50];

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

typedef struct {
	TipoChave Chave;
	Tipochave Nome;
	TipoChave Altura;
	TipoChave Peso;
	TipoChave AnoNascimento;
	Tipochave Universidade;
	Tipochave CidadeNascimento;
	Tipochave EstadoNascimento;
 /* outros componentes */
} TipoItem;

TipoItem criaTipoItem(int valor, char nome[50], int altura, int peso, int anoNascimento, char universidade[50], char cidadeNascimento[50], char estadoNascimento[50]) {
	TipoItem item;
	item.Chave = valor;
	strcpy(item.Nome, nome);
	item.Altura = altura;
	item.Peso = peso;
	item.AnoNascimento = anoNascimento;
	strcpy(item.Universidade, universidade);
	strcpy(item.CidadeNascimento, cidadeNascimento);
	strcpy(item.EstadoNascimento, estadoNascimento);
	return item;
}

typedef struct Celula_str *Apontador;

typedef struct Celula_str {
	TipoItem Item;
	Apontador Prox;
} Celula;

typedef struct {
	Apontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista)
{
	Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
	Lista->Ultimo = Lista->Primeiro;
	Lista->Primeiro->Prox = NULL;
}

void InserePrimeiro(TipoItem x, TipoLista *Lista) {
	Apontador novoItem = (Apontador) malloc(sizeof(Celula));
	if((Lista) == NULL)
		Lista->Ultimo = novoItem;
	novoItem->Item = x;
	novoItem->Prox = Lista->Primeiro->Prox;
	Lista->Primeiro->Prox = novoItem;
}

void InsereUltimo(TipoItem x, TipoLista *Lista) {
	Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
	Lista->Ultimo = Lista->Ultimo->Prox;
	Lista->Ultimo->Item = x;
	Lista->Ultimo->Prox = NULL;
}

void inserir(TipoItem x, TipoLista *Lista, int position) {
	Apontador novoItem = (Apontador) malloc(sizeof(Celula));
	Apontador Aux;
	Aux = Lista->Primeiro;
	int contador = 1;
	while (contador < position) {
		Aux = Aux->Prox;
		contador++;
	}
	novoItem->Item = x;
	novoItem->Prox = Aux->Prox;
	Aux->Prox = novoItem;
}

void Imprime(TipoLista Lista) {
	Apontador Aux;
	Aux = Lista.Primeiro->Prox;
	int i = 0;
	while (Aux != NULL) {
		printf("[%d] ## %s ## %d ## %d ## %d ## %s ## %s ## %s ##\n", i, Aux->Item.Nome, Aux->Item.Altura, Aux->Item.Peso, Aux->Item.AnoNascimento, Aux->Item.Universidade, Aux->Item.CidadeNascimento, Aux->Item.EstadoNascimento);
		Aux = Aux->Prox;
		i++;
	}
}

int RemovePrimeiro(TipoLista *Lista, TipoItem *item)
{
	if((Lista) == NULL) {
		printf("lista vazia!\n");
		return 0;
	}
	Apontador Cabeca = Lista->Primeiro->Prox;
	*item = Cabeca->Item;
	printf("(R) %s\n", item->Nome);
	Lista->Primeiro->Prox = Cabeca->Prox;
	Cabeca->Prox = NULL;
	free(Cabeca);
	return 1;
}

int RemoveUltimo(TipoLista *Lista, TipoItem *item) {
	if((Lista) == NULL) {
		printf("lista vazia!\n");
		return 0;
	}
	else {
		Apontador anterior = Lista->Primeiro;
		while(anterior->Prox->Prox != NULL) {
			anterior = anterior->Prox;
		}
		TipoItem item = Lista->Ultimo->Item;
		printf("(R) %s\n", item.Nome);
		anterior->Prox = NULL;
		free(Lista->Ultimo);
		Lista->Ultimo = anterior;
		return 1;
	}
}

int RemoveElementoNaPosicaoK(TipoLista *Lista, int k, TipoItem *item) {
	if((Lista) == NULL)
		return 0;
	if(k==1)
		return RemovePrimeiro(Lista, item);
	Apontador anterior = Lista->Primeiro;
	Apontador elemento = anterior->Prox;
	int pos = 1;
	while(elemento->Prox != NULL && pos != k) {
		anterior = elemento;
		elemento = elemento->Prox;
		pos++;
	}

	if(elemento->Prox == NULL)
		Lista->Ultimo = anterior;
	anterior->Prox = elemento->Prox;
	*item = elemento->Item;
	printf("(R) %s\n", item->Nome);
	free(elemento);
	return 1;
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


int main(int argc, char const *argv[]) {

	int i = 0, j = 0;
	TipoLista lista;

	t_jogador jogador[3922];
	t_jogador subConjJogador[600];

	char idJogador[30];
	char *tmp;
	char *token;
	char linha[400];
	char **res = NULL;


	// Abertura do arquivo players.csv
	FILE *arquivo = fopen("/tmp/players.csv", "r");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	/**
	 * Para descartar a primeira linha do
	 * do arquivo player.csv que contém
	 * apenas o título das colunas
	 */
	fgets(linha, sizeof(linha), arquivo);



	while (fgets(linha, sizeof(linha), arquivo)) {

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

	FLVazia(&lista);

	for (i = 0; i < j; ++i)
	{
		TipoItem item = criaTipoItem(subConjJogador[i].id, subConjJogador[i].nome, subConjJogador[i].altura, subConjJogador[i].peso, subConjJogador[i].anoNascimento, subConjJogador[i].universidade, subConjJogador[i].cidadeNascimento, subConjJogador[i].estadoNascimento);
		InsereUltimo(item, &lista);
	}

	int count = 0;

	input(linha, sizeof(linha));

	input(linha, sizeof(linha));

	for (int i = 0; i < 32; ++i) {
		input(linha, sizeof(linha));

		split( linha, " ", &res, &count );

		switch(count) {
			case 1:
				if (strcmp(res[0], "RI") == 0)
				{
					TipoItem primeiroItem;
					//printf("(R) %s\n", primeiroItem.Nome);
					RemovePrimeiro(&lista, &primeiroItem);
				}
				if (strcmp(res[0], "RF") == 0)
				{
					TipoItem ultimoItem;
					//printf("(R) %s\n", ultimoItem.Nome);
					RemoveUltimo(&lista, &ultimoItem);
				}
				break;
			case 2:
				if (strcmp(res[0], "II") == 0)
				{
					TipoItem item = criaTipoItem(jogador[atoi(res[1])].id, jogador[atoi(res[1])].nome, jogador[atoi(res[1])].altura, jogador[atoi(res[1])].peso, jogador[atoi(res[1])].anoNascimento, jogador[atoi(res[1])].universidade, jogador[atoi(res[1])].cidadeNascimento, jogador[atoi(res[1])].estadoNascimento);
					InserePrimeiro(item, &lista);
				}
				if (strcmp(res[0], "IF") == 0)
				{
					TipoItem item = criaTipoItem(jogador[atoi(res[1])].id, jogador[atoi(res[1])].nome, jogador[atoi(res[1])].altura, jogador[atoi(res[1])].peso, jogador[atoi(res[1])].anoNascimento, jogador[atoi(res[1])].universidade, jogador[atoi(res[1])].cidadeNascimento, jogador[atoi(res[1])].estadoNascimento);
					InsereUltimo(item, &lista);
				}
				if (strcmp(res[0], "R*") == 0)
				{
					TipoItem item;
					RemoveElementoNaPosicaoK(&lista, atoi(res[1]) + 1, &item);
				}
				break;
			case 3:
				if (strcmp(res[0], "I*") == 0)
				{
					TipoItem item = criaTipoItem(jogador[atoi(res[2])].id, jogador[atoi(res[2])].nome, jogador[atoi(res[2])].altura, jogador[atoi(res[2])].peso, jogador[atoi(res[2])].anoNascimento, jogador[atoi(res[2])].universidade, jogador[atoi(res[2])].cidadeNascimento, jogador[atoi(res[2])].estadoNascimento);
					inserir(item, &lista, atoi(res[1]) + 1);
				}
				break;
		}

		free(res);
	}


	Imprime(lista);



/*
	for(i=0; i<3; i++) {
		TipoItem primeiroItem;
		RemovePrimeiro(&lista, &primeiroItem);
		Imprime(lista);
		TipoItem ultimoItem;
		RemoveUltimo(&lista, &ultimoItem);
		Imprime(lista);
	}

	TipoItem item5;
	RemoveElementoNaPosicaoK(&lista, 5, &item5);
	TipoItem item1;
	RemoveElementoNaPosicaoK(&lista, 1, &item1);
	TipoItem item7;
	RemoveElementoNaPosicaoK(&lista, 7, &item7);
	printf("--------------\n");

	Imprime(lista);
	*/
	return 0;
}
