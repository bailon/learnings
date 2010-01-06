/**************************************************************************************************
 * Shellsort - Algoritmo de Ordenação                                                             *
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
void shellsort(int *v, int size) {
	int i, j, increment, temp;
	increment = size / 2;
	
	while (increment > 0) {
	for (i = increment; i < size; i++)
	{
		j = i;
		temp = v[i];
		while ((j >= increment) && (v[j-increment] > temp))
		{
			v[j] = v[j - increment];
			j = j - increment;
		}
		v[j] = temp;
	}
 
	if (increment == 2)
		increment = 1;
	else 
		increment = (int) (increment / 2.2);
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
			shellsort(v, i);
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
			shellsort(v, i);
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
			shellsort(v, i);
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
