#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_THREAD 9                 //Numero de elemetos na linha/coluna
#define MAX_THREAD 30

typedef struct{
  int vetor [N_THREAD][N_THREAD];
  int linha;
  int coluna;
  int valorAVerificar;
}dados;


/*Procura o valor na linha, funcao para backtrac, dicask*/
int procuraValorLinha(dados *data){
  int i, linha=data->linha;
    for(i=0; i<N_THREAD; i++){
      if(data->valorAVerificar==data->vetor[linha][i])
	return 1;
    }
  return 0;
}

/*Procura o valor na coluna, funcao para backtrack, dicas*/
int procuraValorColuna(dados *data){
  int i, coluna=data->coluna;
  for(i=0; i<N_THREAD; i++){
    if(data->valorAVerificar==data->vetor[i][coluna])
      return 1;
  }
  return 0;
}

/*Procura o valor no quadrado, funcao para backtrack, dicas*/
int procuraValorQuadrado(dados *data){
  int i,inicioColuna=(data->coluna/3)*3, inicioLinha=(data->linha/3)*3;
  int num=data->valorAVerificar;
  for(i=0; i<9; i++){
    if (data->vetor[inicioLinha + (i%3)][inicioColuna + (i/3)] == num)
       return 1;
  }
  return 0;
}

/*Copiar array*/

void copiaArray(dados *data, int (*matriz)[N_THREAD]){
  int i=0, j=0;
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      data->vetor[i][j]=matriz[i][j];
    }
  }
}

/*Imprime o array*/

void imprimeArray(dados *data){
  int i, j;
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      printf("%d ", data->vetor[i][j]);
      if(j==8)
	printf("\n");
    }
  }
}

/*Resolve o sudoku*/
/*Ideia do algoritmo: resolucao por backtrack, cada vez que ele achar uma posicao vaga,
o algoritmo cria uma thread nova para um valor a ser testado.
Ex: se numa posicao vaga existirem 3 numeros possiveis, serao criadas 3 threads
*/

void* resolveSudoku(void *v){
  int numero, linha, coluna;
  dados *temp=v;
  dados data=*temp;
  linha=data.linha;
  coluna=data.coluna;
  if(data.linha<9 && data.coluna<9){
    if(data.vetor[linha][coluna]==0){        // Achou posicao livre
      for(numero=1; numero<10; numero++){    // Sao os valores que serao testados
	data.valorAVerificar=numero;
	if(!procuraValorLinha(&data) && !procuraValorColuna(&data) && !procuraValorQuadrado(&data)){
	  dados data2=data;
	  data2.vetor[linha][coluna]=numero;
	  if(data2.linha==8 && data2.coluna==8){      //Chegou na ultima posicao, tabuleiro completo
	    imprimeArray(&data2);
	    printf("\n");                             
	  }else if(data2.coluna==8){                  //Muda de linha, zera coluna
	    data2.linha++;
	    data2.coluna=0;
	    pthread_t thread;
	    pthread_create(&thread, NULL, resolveSudoku, (void*)&data2);
	    pthread_join(thread, NULL);
	  }else{                                      //Avanca a coluna na mesma linha
	    data2.coluna++;
	    pthread_t thread;
	    pthread_create(&thread, NULL, resolveSudoku, (void*)&data2);
	    pthread_join(thread, NULL);
	  }	   
	}
      }
    }
    else{                                           //A posicao ja contem um numero
      if(data.linha==8 && data.coluna==8)
	imprimeArray(&data);
      else if(data.coluna==8){                      //Zera coluna e avanca linha
	dados data2=data;
	data2.linha++;
	data2.coluna=0;
	pthread_t thread;
	pthread_create(&thread, NULL, resolveSudoku, (void*)&data2);
	pthread_join(thread, NULL);
      }
      else{                                         //Avanca coluna na mesma linha
	dados data2=data;
	data2.coluna++;
	pthread_t thread;
	pthread_create(&thread, NULL, resolveSudoku, (void*)&data2);
	pthread_join(thread, NULL);
      }
    }
  }
  return NULL;
}

int main(){

int vetor[N_THREAD][N_THREAD]={
    {9,4,0,1,0,2,0,5,8},
    {6,0,0,0,5,0,0,0,4},
    {0,0,2,4,0,3,1,0,0},
    {0,2,0,0,0,0,0,6,0},
    {5,0,8,0,2,0,4,0,1},
    {0,6,0,0,0,0,0,8,0},
    {0,0,1,6,0,8,7,0,0},
    {7,0,0,0,4,0,0,0,3},
    {4,3,0,5,0,9,0,1,2}
  };

  dados data;
  data.linha=0;
  data.coluna=0;
  copiaArray(&data, vetor);
  pthread_t thread;
  pthread_create(&thread, NULL, resolveSudoku, (void*) &data);
  pthread_join(thread, NULL);
  
  return 0;
}
