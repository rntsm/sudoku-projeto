#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_THREAD 9                 //Numero de elemetos na linha/coluna

typedef struct data{
  int (*vetor)[N_THREAD];
  int linha;
  int coluna;
  int valorAVerificar;
}data;


/*Procura o valor na linha, funcao para backtrac, dicask*/
int procuraValorLinha(data *data){
  int i, linha=data->linha;
    for(i=0; i<N_THREAD; i++){
      if(data->valorAVerificar==data->vetor[linha][i])
	return 1;
    }
  return 0;
}

/*Procura o valor na coluna, funcao para backtrack, dicas*/
int procuraValorColuna(data *data){
  int i, coluna=data->coluna;
  for(i=0; i<N_THREAD; i++){
    if(data->valorAVerificar==data->vetor[i][coluna])
      return 1;
  }
  return 0;
}

/*Procura o valor no quadrado, funcao para backtrack, dicas*/
int procuraValorQuadrado(data *data){
  int i,inicioColuna=(data->coluna/3)*3, inicioLinha=(data->linha/3)*3;
  int num=data->valorAVerificar;
  for(i=0; i<9; i++){
    if (data->vetor[inicioLinha + (i%3)][inicioColuna + (i/3)] == num)
       return 1;
  }
  return 0;
}

/*Cria as dicas para o usuario*/
void* dicas(void *v){
  int i, j, numero;
  int(*vetor)[N_THREAD]=v;
  data *aux=malloc(sizeof(data));

  aux->vetor = vetor;//esta dando erro aqui
  
  for(i=0;i<N_THREAD;i++){//i e j sao para percorrer a matriz >
	for(j=0;j<N_THREAD;j++){
		if(aux->vetor[i][j] == 0){//se for zero vai verificar que numeros podem ser
			aux->linha = i;
			aux->coluna = j;
			printf("(");
			for(numero=1;numero<10;numero++){//aqui vai testar todos os numeros
				aux->valorAVerificar = numero;
				if(!procuraValorQuadrado(aux) && !procuraValorColuna(aux)
					&& !procuraValorLinha(aux)){
				printf("%d", numero);
				}
			}
			printf(") ");
		}	
		else{
			printf("%d ", aux->vetor[i][j]);
		}		
	}
		printf("\n");
  }

  return NULL;
}

int main(){
  
  int vetor[N_THREAD][N_THREAD]={
    {0,6,1,0,0,0,0,9,1},
    {4,3,0,0,9,5,0,6,0},
    {9,0,0,1,0,2,0,0,3},
    {0,0,0,4,0,1,0,0,9},
    {5,0,9,0,0,0,7,0,1},
    {6,0,0,2,0,9,0,0,0},
    {3,0,0,9,0,8,0,0,6},
    {0,8,0,7,3,0,0,4,2},
    {0,9,0,0,0,0,3,1,0}
  };

  pthread_t thread;
  pthread_create(&thread, NULL, dicas, (void*)vetor);
  pthread_join(thread, NULL);
  
  return 0;
}
