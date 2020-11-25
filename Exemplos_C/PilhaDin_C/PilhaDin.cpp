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
	Jogador *prox;
} t_jogador;

int tam;


int vazia(t_jogador *PILHA)
{
	if(PILHA->prox == NULL)
		return 1;
	else
		return 0;
}

t_jogador *aloca()
{
	t_jogador *novo=(t_jogador *) malloc(sizeof(t_jogador));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		printf("Novo elemento: "); scanf("%d %s %d", &novo->id, &novo->nome, &novo->altura);
		return novo;
	}
}


void exibe(t_jogador *PILHA)
{
	if(vazia(PILHA)){
		printf("PILHA vazia!\n\n");
		return ;
	}

	t_jogador *tmp;
	tmp = PILHA->prox;
	printf("PILHA:");
	while( tmp != NULL){
		printf("%5d, %s, %d", tmp->id, tmp->nome, tmp->altura);
		tmp = tmp->prox;
	}
	printf("\n        ");
	int count;
	for(count=0 ; count < tam ; count++)
		printf("  ^  ");
	printf("\nOrdem:");
	for(count=0 ; count < tam ; count++)
		printf("%5d", count+1);


	printf("\n\n");
}

void libera(t_jogador *PILHA)
{
	if(!vazia(PILHA)){
		t_jogador *proxNode,
			*atual;

		atual = PILHA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void push(t_jogador *PILHA)
{
	t_jogador *novo=aloca();
	novo->prox = NULL;

	if(vazia(PILHA))
		PILHA->prox=novo;
	else{
		t_jogador *tmp = PILHA->prox;

		while(tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	tam++;
}


t_jogador *pop(t_jogador *PILHA)
{
	if(PILHA->prox == NULL){
		printf("PILHA ja vazia\n\n");
		return NULL;
	}else{
		t_jogador *ultimo = PILHA->prox,
			*penultimo = PILHA;

		while(ultimo->prox != NULL){
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}

		penultimo->prox = NULL;
		tam--;
		return ultimo;
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



	for(i = 0; i < j-1; i++) {
		printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", subConjJogador[i].id, subConjJogador[i].nome, subConjJogador[i].altura, subConjJogador[i].peso, subConjJogador[i].anoNascimento, subConjJogador[i].universidade, subConjJogador[i].cidadeNascimento, subConjJogador[i].estadoNascimento);
	}

	printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", jogador[280].id, jogador[280].nome, jogador[280].altura, jogador[280].peso, jogador[280].anoNascimento, jogador[280].universidade, jogador[280].cidadeNascimento, jogador[280].estadoNascimento);


	return 0;
}
