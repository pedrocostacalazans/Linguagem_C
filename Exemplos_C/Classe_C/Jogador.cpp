#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_LINHA 200

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

int main(int argc, char *argv[]) {

	t_jogador jogador[3922];

	char *token;
	char linha[sizeof(t_jogador)];
	char idJogador[4];
	char *tmp;

	FILE *arquivo = fopen("/tmp/players.csv", "r");
	if(arquivo == NULL) {
		 printf("Erro ao abrir o arquivo.\n");
		 exit(1);
	}

	fgets(linha, sizeof(t_jogador), arquivo);

	int i = 0;

	while (fgets(linha, sizeof(t_jogador), arquivo)) {

		if(linha[strlen(linha)-2] == ',') {
			linha[strlen(linha)-1] = '\0';
			strcat(linha, "nao informado");
		} else {
			linha[strlen(linha)-1] = '\0';
		}


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

	fclose(arquivo);

	scanf("%s",idJogador);

	while(strcmp(idJogador,"FIM") != 0) {

		for(int i = 0; i < 3922; i++) {


			if(atoi(idJogador) == jogador[i].id) {

				printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", jogador[i].id, jogador[i].nome, jogador[i].altura, jogador[i].peso, jogador[i].anoNascimento, jogador[i].universidade, jogador[i].cidadeNascimento, jogador[i].estadoNascimento);

				break;
			}

		}

		scanf("%s",idJogador);
	}

	return(0);
}
