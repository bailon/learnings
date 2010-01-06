/**************************************************************************************************
 * Quicksort - Algoritmo de Ordenação                                                             *
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
// @param	array	Vetor para ser ordenado.
// @param	begin	Posição inicial do vetor.
// @param	end		Posição final do vetor.	
void quicksort(int *array, int begin, int end) {
	int x;

	if (end - begin > 1)
	{
		int pivot = array[begin];
		int l = begin + 1;
		int r = end;
		
		while (l < r) {
			if (array[l] <= pivot)
				l++;
			else
			{
				x = array[l];
				array[l] = array[r];
				array[r] = x;
				r--;
			}
		}
		l--;
		x = array[begin];
		array[begin] = array[l];
		array[l] = x;
		quicksort(array, begin, l);
		quicksort(array, r, end);
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
			v = arrayOrdenado(i);
			start = (double)clock(); 
			quicksort(v, 0, i);
			elapsed = ((double)clock() - start) / 1000;
			media += elapsed;
			
			if (j == 0)
			{
				pior = elapsed;
				melhor = elapsed;
			}
			
			if (elapsed > pior)
				pior = elapsed;
			
			if (elapsed < melhor)
				melhor = elapsed;
		}
		
		printf("%d;%.0f;%.0f;%.0f\n", i, media / 20, pior, melhor);
	}
	
	/* Lista inversa -----------------------------------------------------------------------------*/
	printf("Lista Inversa:\n");
	for (i = 5000; i <= MAX; i = i + 5000)
	{
		media = 0;
		for (j = 0; j < 20; j++)
		{ 
			v = arrayInverso(i);
			start = (double)clock(); 
			quicksort(v, 0, i);
			elapsed = ((double)clock() - start) / 1000;
			media += elapsed;
			
			if (j == 0)
			{
				pior = elapsed;
				melhor = elapsed;
			}
			
			if (elapsed > pior)
				pior = elapsed;
			
			if (elapsed < melhor)
				melhor = elapsed;
		}
		
		printf("%d;%.0f;%.0f;%.0f\n", i, media / 20, pior, melhor);
	}
	
	/* Valores aleatórios ------------------------------------------------------------------------*/
	printf("Lista Aleatoria:\n");
	for (i = 5000; i <= MAX; i = i + 5000)
	{
		media = 0;
		for (j = 0; j < 20; j++)
		{ 
			v = arrayRandom(i);
			start = (double)clock(); 
			quicksort(v, 0, i);
			elapsed = ((double)clock() - start) / 1000;
			media += elapsed;
			
			if (j == 0)
			{
				pior = elapsed;
				melhor = elapsed;
			}
			
			if (elapsed > pior)
				pior = elapsed;
			
			if (elapsed < melhor)
				melhor = elapsed;
		}
		
		printf("%d;%.0f;%.0f;%.0f\n", i, media / 20, pior, melhor);
	}
	
	return 0;
}
