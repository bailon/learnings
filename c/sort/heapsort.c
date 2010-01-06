/**************************************************************************************************
 * Heapsort - Algoritmo de Ordenação                                                              *
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
void heapsort(int *v, int size)
{
	int i, pai, filho, t;
	
	i = size / 2;
	
	while (1)
	{
		if (i > 0)
		{
			i--;
			t = v[i];
		}
		
		else
		{
			size--;
			if (size == 0) return;
			t = v[size];
			v[size] = v[0];
		}
		
		pai = i;
		filho = i * 2 + 1;
		
		while (filho < size)
		{
			if ((filho + 1 < size) && (v[filho + 1] > v[filho]))
				filho++;
				
			if (v[filho] > t)
			{
				v[pai] = v[filho];
				pai = filho;
				filho = pai * 2 + 1;
			}
			else break;
		}
		v[pai] = t;
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
			heapsort(v, i - 1);
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
			heapsort(v, i - 1);
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
			heapsort(v, i - 1);
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
