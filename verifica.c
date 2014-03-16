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

/*Verifica linha*/
void* verificaLinha(void *v){
  int (*vetor)[N_THREAD]=v;
  int line=0;
  for(line=0; line<9; line++){
    int k,i, contagem=0, flag=0, linha=line;
    for (i=0; i<9&&flag==0; i++){
      int comparacao=vetor[linha][i];
      for (k=0; k<9&&flag==0; k++){
	if(vetor[linha][k]==comparacao){
	  contagem++;
	}
      }
      if(contagem>1){
	printf("Linha com %d erro \n",linha+1);
	flag=1;
      }
      contagem=0;
    }
  }
  return NULL;
}

/*Verifica coluna*/
void* verificaColuna(void *v){
  int (*vetor)[N_THREAD]=v;
  int column=0;
  for(column=0; column<9; column++){
    int k,i, contagem=0, flag=0, coluna=column;
    for (i=0; i<9&&flag==0; i++){
      int comparacao=vetor[i][coluna];
      for (k=0; k<9&&flag==0; k++){
	if(vetor[k][coluna]==comparacao){
	  contagem++;
	}
      }
      if(contagem>1){
	printf("Coluna com %d erro \n",coluna+1);
	flag=1;
      }
      contagem=0;
    }
  }
  return NULL;
}

/*Verifica quadrado*/
void* verificaQuadrado(void *v){
  int (*vetor)[N_THREAD]=v;
  int linha, coluna, contagem=0, flag=0;
  for (linha=0; linha<9&&flag==0; linha+=3){
    for (coluna=0; coluna<9&&flag==0; coluna+=3){
      int valorProcura;
      for(valorProcura=1; valorProcura<=9&&flag==0; valorProcura++){
	int i;
	for(i=0; i<9; i++){
	  if(vetor[linha+(i%3)][coluna+(i/3)]==valorProcura){
	    contagem++;
	  }
	}
	if(contagem>1){
	  printf("Quadrado com erro\n");
	  flag=1;
	}
	contagem=0;
      }
    }
  }

  return NULL;
}

/*Verifica se o tabuleiro foi preenchido corretamente*/
void verificaTabuleiro(int (*vetor)[N_THREAD]){
  pthread_t thread[3];                 
  //Changed, 3 threads, uma para linha, coluna, quadrado
  pthread_create(&thread[0], NULL, verificaLinha, (void*)vetor);
  pthread_create(&thread[1], NULL, verificaColuna, (void*)vetor);
  pthread_create(&thread[2], NULL, verificaQuadrado, (void*)vetor);
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);  
  pthread_join(thread[2], NULL);
}

int main(){
  int vetor[N_THREAD][N_THREAD]={
    {8,6,1,3,4,2,2,5,5},
    {4,3,2,8,9,5,1,6,3},
    {7,5,9,1,6,7,4,8,8},
    {2,7,8,4,5,9,9,9,9},
    {5,4,9,6,8,3,7,2,1},
    {1,1,1,1,1,1,1,1,1},
    {3,2,4,9,1,8,5,7,6},
    {1,8,5,7,3,6,9,4,2},
    {7,9,6,5,2,4,8,1,8}
  };
  verificaTabuleiro(&vetor[0]);
  
  
  return 0;
}
