/**************************************************************************************************
 * Bubblesort - Algoritmo de Ordenação                                                            *
 *																								  *
 * @author	Bruno Rodrigues <bruno.ufpel@gmail.com>                                               *
 * @date	2008/09/03                                                                            *
 **************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arrays.c"

#define MAX 100000



// @brief	Algoritmo de ordenação básico.
// @param	v		Vetor para ser ordenado.
// @param	size	Tamanho do vetor.	
void bubblesort (int *v, int size)
{
	int i, j;
	
	for (i = size - 1; i > 0; i--)	// Varia com o tamanho do vetor
		for (j = 0; j < i; j++)		// Varre cada posição, trocando de posição se
			if (v[j] > v[j+1])		//   o elemento for menor
			{
				int temp;			// Faz a troca dos elementos
			
				temp = v[j];
				v[j] = v[j+1];
				v[j+1] = temp;
			}
}



int main (int argc, char *argv)
{
	int *v;
	int i, j;
	double elapsed, start, media, pior, melhor;
	
	/* Lista ordenada ----------------------------------------------------------------------------*/
	printf("Lista Ordenada\n");
	for (i = 5000; i <= MAX; i = i + 5000)
	{
		media = 0;
		for (j = 0; j < 20; j++)
		{ 
			v = arrayOrdenado(i);							// Gera o vetor ordenado
			start = (double)clock(); 						// Hora do inicio da execução 
			bubblesort(v, i);								// Executa o algoritmo de ordenação
			elapsed = ((double)clock() - start) / 1000;		// Tempo após a execução, em ms
															//   pegando o tempo decorrido.
			media += elapsed;								// Acumula o tempo de execução
			
			if (j == 0)										// Guarda o melhor e o pior tempo
			{												// Guarda se for a primeira execução
				pior = elapsed;
				melhor = elapsed;
			}
			
			if (elapsed > pior)								// Pior tempo (maior)
				pior = elapsed;

			if (elapsed < melhor)							// Melhor tempo (menor)
				melhor = elapsed;
		}
		
		// Imprime na tela uma saída em CSV do número de elementos, tempo médio, pior tempo e
		// melhor tempo, respectivamente.
		printf("%d;%.0f;%.0f;%.0f\n", i, media / 20, pior, melhor);
	}
		
	/* Lista inversa -----------------------------------------------------------------------------*/
	printf("Lista Inversa:\n");
	for (i = 5000; i <= MAX; i = i + 5000)
	{
		media = 0;
		for (j = 0; j < 20; j++)
		{ 
			v = arrayInverso(i);							// Gera o vetor inverso
			start = (double)clock(); 						// Hora do inicio da execução 
			bubblesort(v, i);								// Executa o algoritmo de ordenação
			elapsed = ((double)clock() - start) / 1000;		// Tempo após a execução, em ms
															//   pegando o tempo decorrido.
			media += elapsed;								// Acumula o tempo de execução
			
			if (j == 0)										// Guarda o melhor e o pior tempo
			{												// Guarda se for a primeira execução
				pior = elapsed;
				melhor = elapsed;
			}
			
			if (elapsed > pior)								// Pior tempo (maior)
				pior = elapsed;

			if (elapsed < melhor)							// Melhor tempo (menor)
				melhor = elapsed;
		}
		
		// Imprime na tela uma saída em CSV do número de elementos, tempo médio, pior tempo e
		// melhor tempo, respectivamente.
		printf("%d;%.0f;%.0f;%.0f\n", i, media / 20, pior, melhor);
	}
	
	/* Valores aleatórios ------------------------------------------------------------------------*/
	printf("Lista Aleatoria:\n");
	for (i = 5000; i <= MAX; i = i + 5000)
	{
		media = 0;
		for (j = 0; j < 20; j++)
		{ 
			v = arrayOrdenado(i);							// Gera o vetor aleatório
			start = (double)clock(); 						// Hora do inicio da execução 
			bubblesort(v, i);								// Executa o algoritmo de ordenação
			elapsed = ((double)clock() - start) / 1000;		// Tempo após a execução, em ms
															//   pegando o tempo decorrido.
			media += elapsed;								// Acumula o tempo de execução
			
			if (j == 0)										// Guarda o melhor e o pior tempo
			{												// Guarda se for a primeira execução
				pior = elapsed;
				melhor = elapsed;
			}
			
			if (elapsed > pior)								// Pior tempo (maior)
				pior = elapsed;

			if (elapsed < melhor)							// Melhor tempo (menor)
				melhor = elapsed;
		}
		
		// Imprime na tela uma saída em CSV do número de elementos, tempo médio, pior tempo e
		// melhor tempo, respectivamente.
		printf("%d;%.0f;%.0f;%.0f\n", i, media / 20, pior, melhor);
	}
	
	return 0;
}
