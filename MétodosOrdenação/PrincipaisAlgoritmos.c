#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Principais métodos de ordenação envolvendo estruturas

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

//Ordenação Strings ordem alfabética
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


//Bolha
void bubble_sort (t_jogador *subConjJogador, int n) {
	int k, j;
	t_jogador aux;

	for (k = n - 1; k > 0; k--) {

		for (j = 0; j < k; j++) {

			if (subConjJogador[j].anoNascimento > subConjJogador[j + 1].anoNascimento) {
				aux = subConjJogador[j];
				subConjJogador[j] = subConjJogador[j + 1];
				subConjJogador[j + 1] = aux;
			}
		}
	}
}


//Heapsort
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


//Inserção
void insert_sort(t_jogador *subConjJogador, int n) {
  int i, j;

  for(i = 1; i < n; i++) {
    t_jogador x = subConjJogador[i];
    j = i-1;
    while(j>=0 && subConjJogador[j].anoNascimento > x.anoNascimento) {
      subConjJogador[j+1] = subConjJogador[j];
      j--;
    }
    subConjJogador[j+1] = x;
  }
}


//Mergesort com pesquisa binária
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


//Quicksort
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


//Shellsort
void shellSort(t_jogador *subConjJogador, int tam) {
	int i , j;
	t_jogador value;
	
	int gap = 1;
  
	do {
		gap = 3*gap+1;
	} while(gap < tam);
  
	do {
		gap /= 3;
		for(i = gap; i < tam; i++) {
			value = subConjJogador[i];
			j = i - gap;
    
			while (j >= 0 && value.peso < subConjJogador[j].peso) {
				subConjJogador[j + gap] = subConjJogador[j];
				j -= gap;
			}
			subConjJogador[j + gap] = value;
		}
	} while(gap > 1);
}