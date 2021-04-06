#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define TOTAL_MUSIC_NUMBER 170625
#define MAX_LINE_LENGTH 1000

typedef struct Musica {
	char id[100], nome[100], key[100], artists[1000], release_date[100];
	double acousticness, danceability, energy, valence , liveness, loudness, speechiness, instrumentalness;
	float tempo;
	int duration_ms, popularity, year;
} t_musica;

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

void tiraDigito (char *v, char letra, int tam)
{
	int i = 0, j;

	for (j = 0; j <= tam; ++j){
		if (v[j] != letra) v[i++] = v[j];
	}
	i -= 1;
	v[i] = '\0';
}

int substituirDigito (char *v, char letra, int tam)
{
	int i = 0, j;

	for (j = 0; j <= tam; ++j){
		if (v[j] == letra) v[j] = ',';
	}
	i -= 1;
	return i;
}

void formatarData(char *data, char *dataFinal) {
	char **resul = NULL;
	int count2 = 0;
	int rc1;
	char dataTeste[15] = "";

	dataFinal[0] = '\0';
	rc1 = split( data, "-", &resul, &count2 );

	if( rc1 ) {
		printf("Error: %s errno: %d \n", strerror(errno), errno);
	}

	if (count2 == 1) {
		strcat(dataTeste, "01");
		strcat(dataTeste, "/");
		strcat(dataTeste, "01");
		strcat(dataTeste, "/");
		strcat(dataTeste, resul[0]);
		strcpy(dataFinal, dataTeste);
	} else {
		strcat(resul[2], "/");
		strcat(resul[2], resul[1]);
		strcat(resul[2], "/");
		strcat(resul[2], resul[0]);
		strcpy(dataFinal, resul[2]);
	}

	free(resul);
}

void selectionSort(t_musica **subConjMusica, int low, int high) {

	int i, rh;
	t_musica *temp;

	if(low < high) {
		rh = low;
		for(i = low+1; i <= high; i++) {
			if(strcmp(subConjMusica[i]->nome,subConjMusica[rh]->nome) < 0)
				rh = i;
		}
		temp = subConjMusica[low];
		subConjMusica[low] = subConjMusica[rh];
		subConjMusica[rh] = temp;
		selectionSort(subConjMusica, low+1, high);
	}
}

int main() {
	char linha[MAX_LINE_LENGTH];
	char id[50], dataFinal[30];

	//alocacao do array de strings
  t_musica **totalMusicList;
  totalMusicList = (t_musica **) malloc(sizeof(t_musica *) * TOTAL_MUSIC_NUMBER);

  //alocacao das strings contidas no array
  for (int i = 0; i < TOTAL_MUSIC_NUMBER; i++)
		totalMusicList[i] = (t_musica *)malloc(sizeof(char *) * MAX_LINE_LENGTH);

	t_musica **subConjMusica;
	subConjMusica = (t_musica **)malloc(sizeof(t_musica *) * 100);

	FILE *arquivo = fopen("data.csv", "r");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	char **res = NULL;
	int count = 0;
	int rc, i = 0, j;

	fgets(linha, MAX_LINE_LENGTH, arquivo);

	while (fgets(linha, MAX_LINE_LENGTH, arquivo)) {
		int tam = strlen(linha);

		for (j = 0; j < tam; ++j)
		{
			if (linha[j] == '\"')
			{
				j++;
				while(linha[j] != '\"') {
					if (linha[j] == ',')
					{
						linha[j] = ';';
					}
					j++;
				}
			}
		}

		tiraDigito(linha, '\"', tam);
		tiraDigito(linha, '\'', tam);

		rc = split( linha, ",", &res, &count );

		if( rc ) {
			printf("Error: %s errno: %d \n", strerror(errno), errno);
		}

		substituirDigito(res[3], ';', strlen(res[3]));

		totalMusicList[i]->valence = atof(res[0]);
		totalMusicList[i]->year = atoi(res[1]);
		totalMusicList[i]->acousticness = atof(res[2]);
		strcpy(totalMusicList[i]->artists, res[3]);
		totalMusicList[i]->danceability = atof(res[4]);
		totalMusicList[i]->duration_ms = atof(res[5]);
		totalMusicList[i]->energy = atof(res[6]);
		strcpy(totalMusicList[i]->id, res[8]);
		totalMusicList[i]->instrumentalness = atof(res[9]);
		strcpy(totalMusicList[i]->key, res[10]);
		totalMusicList[i]->liveness = atof(res[11]);
		totalMusicList[i]->loudness = atof(res[12]);
		strcpy(totalMusicList[i]->nome, res[14]);
		totalMusicList[i]->popularity = atoi(res[15]);
		totalMusicList[i]->speechiness = atof(res[17]);
		totalMusicList[i]->tempo = atof(res[18]);
		if (strlen(res[16]) > 4) {
			formatarData(res[16], dataFinal);
			strcpy(totalMusicList[i]->release_date, dataFinal);
		} else if (strcmp(res[16], "") == 0) {
			strcpy(totalMusicList[i]->release_date, "01");
		}
		
		i++;

		free(res);
	}

	fclose(arquivo);

	j = 0;

	scanf("%s",id);

	while(strcmp(id,"FIM") != 0) {

		for(int i = 0; i < 170625; i++) {


			if(strcmp(totalMusicList[i]->id, id) == 0) {

				subConjMusica[j] = totalMusicList[i];
				j++;
				break;
			}

		}

		scanf("%s",id);
	}

	selectionSort(subConjMusica, 0, j-1);

	for (i = 0; i < j; ++i) {
		printf("%s ## %s ## %s ## %s ## %lg ## %lg ## %lg ## %lg ## %lg ## %lg ## %lg ## %d\n", subConjMusica[i]->id, subConjMusica[i]->artists, subConjMusica[i]->nome, subConjMusica[i]->release_date, subConjMusica[i]->acousticness, subConjMusica[i]->danceability, subConjMusica[i]->instrumentalness, subConjMusica[i]->liveness, subConjMusica[i]->loudness, subConjMusica[i]->speechiness, subConjMusica[i]->energy, subConjMusica[i]->duration_ms);
	}

	free(totalMusicList);
	free(subConjMusica);
	return 0;
}
