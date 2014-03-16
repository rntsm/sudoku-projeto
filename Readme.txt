MC504

Grupo:

Fabio Yudi Murakami
Renato Yoshio Soma

Estrategia adotada:

Para o módulo de verificação, utilizamos 3 threads que percorrem o tabuleiro, uma para linha, outra para coluna e outra para o quadrado interno. 
	Ponto positivo da estrategia: Não há grande consumo de memória.
	Ponto negativo: Mais lento que se tivessemos usado uma thread para cada linha/coluna/quadrado.

Para o módulo de dicas, usamos uma thread que verificou o tabuleiro e procurou os valores possiveis.
	Ponto positivo: Baixo consumo de memória
	Ponto negativo: Se tivessemos utilizado uma thread para verificar a validade de cada um dos números de 1-9, usariamos mais memoria, mas teriamos um ganho de performace
	
Para o módulo de resolver o sudoku, utilizamos um número variável de threads, que depende do tabuleiro a ser iniciado. Toda vez que encontramos uma posicao válida ("0"), utilizamos funções que verificam se um número de 1-9 é válido na posição. Se ele for válido, criamos uma thread para ele e usamos a mesma função novamente, para a posição seguinte (backtrack). Repetimos o procedimento para todos os outros números válidos.
	Ponto positivo: Algoritmo veloz
	Ponto negativo: Alto consumo de memória, visto que a cada número válido chamamos a função novamente, o que cria várias pilhas para as diferentes threads.
