/**************************************************************************************************
 * Função de criação de vetores para o trabalho de algoritmos de ordenação	                      *
 *																								  *
 * @author	Bruno Rodrigues <bruno.ufpel@gmail.com>                                               *
 * @date	2008/09/03                                                                            *
 **************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



// @brief	Gera um vetor de inteiros ordenados crescentemente, variando de 0 a n e de tamanho n.
// @param	n	Número de elementos do array.
// @return	Vetor de elementos ordenados.
int * arrayOrdenado (int n)
{
	int i, *v;
	
	v = malloc(n * sizeof(int));	// Aloca memória para um vetor de inteiros de tamanho n
	
	for (i = 0; i < n; i++)
		v[i] = i;
	
	return v;
}



// @brief	Gera um vetor de inteiros ordenados inversamente, variando de 0 a n e de tamanho n.
// @param	n	Número de elementos do array.
// @return	Vetor de elementos ordenados inversamente.
int * arrayInverso (int n)
{
	int i, *v;
	
	v = malloc(n * sizeof(int));	// Aloca memória para um vetor de inteiros de tamanho n
	
	for (i = 0; i <= n; ++i)
		v[i] = n - i;
	
	return v;
}



// @brief	Gera um vetor de inteiros aleatório, variando de 0 a n e de tamanho n.
// @param	n	Número de elementos do array.
// @return	Vetor de elementos aleatórios.
int * arrayRandom (int n)
{
	int i, *v;
	
	srand(time(NULL));				// Gera a semente para o rand
	
	v = malloc(n * sizeof(int));	// Aloca memória para um vetor de inteiros de tamanho n
	
	for (i = 0; i <= n; i++)
		v[i] = rand() % n;
	
	return v;
}
