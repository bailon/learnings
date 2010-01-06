/******************************************************************************
 *                     Trabalho de Estruturas de Dados 2
 *          Universidade Federal de Pelotas - Ciência da Computação
 *
 * Aluno	: Bruno Martins Rodrigues
 * Email	: bruno.ufpel@gmail.com
 * Data		: 15 de Outubro de 2008
 ******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX		1024
#define ENTRADA	"dna.in"
#define SAIDA	"dna.out"

typedef struct dna
{	int set;
	struct dna *a;
	struct dna *c;
	struct dna *g;
	struct dna *t;
} DNA;




/******************************************************************************
 * cria_no
 * Cria um nó do DNA
 ******************************************************************************/
DNA * cria_no ()
{
	DNA *no;
	if ((no = malloc(sizeof(DNA))) == NULL)
	{ 
        	printf("Erro - Nao foi possivel alocar memoria para o no.\n");
        	exit(0);
    }
	
	no->set	= 0;
	no->a	= NULL;
	no->c	= NULL;
	no->g	= NULL;
	no->t	= NULL;

	return no;
}




/******************************************************************************
 * insere_no
 * Insere um nó na arvore em seu local correto.
 ******************************************************************************/
void insere (DNA **arv, char linha[MAX], int i)
{
	DNA *no;
	
	for (no = *arv; linha[i] != '\0'; i++)
	{	
		switch (linha[i])
		{
			case 'A':
				if (no->a == NULL)
					no->a = cria_no();
				no = no->a;		
				break;
				
			case 'C':
				if (no->c == NULL)
					no->c = cria_no();
				no = no->c;		
				break;
				
			case 'G':
				if (no->g == NULL)
					no->g = cria_no();
				no = no->g;		
				break;
				
			case 'T':
				if (no->t == NULL)
					no->t = cria_no();
				no = no->t;		
				break;
		}	
	}
}




/******************************************************************************
 * confere
 * Passa a segunda lista e marca os nós repetidos.
 ******************************************************************************/
void confere (DNA **arv, char linha[MAX], int i)
{
	DNA *no;

	for (no = *arv; linha[i] != '\0'; i++)
	{	
		switch (linha[i])
		{
			case 'A':
				if (no->a == NULL)
					return;
				else
					no->set = 1;
				no = no->a;		
				break;
				
			case 'C':
				if (no->c == NULL)
					return;				
				else
					no->set = 1;
				no = no->c;
				break;
				
			case 'G':
				if (no->g == NULL)
					return;
				else
					no->set = 1;
				no = no->g;
				break;
				
			case 'T':
				if (no->t == NULL)
					return;
				else
					no->set = 1;
				no = no->t;
				break;
		}	
	}
}




/******************************************************************************
 * tamanho
 * Conta o tamanho do maior no igual.
 ******************************************************************************/
int tamanho (DNA *no)
{
	int ia = 0;
	int ic = 0;
	int ig = 0;
	int it = 0;
	
	if (no->set == 1)
	{
		if (no->a != NULL)
			ia = 1 + tamanho(no->a);
		if (no->c != NULL)
			ic = 1 + tamanho(no->c);
		if (no->g != NULL)
			ig = 1 + tamanho(no->g);
		if (no->t != NULL)
			it = 1 + tamanho(no->t);
		
		if (ia >= ic && ia >= ig && ia >= it)
			return ia;
		if (ic >= ia && ic >= ig && ic >= it)
			return ic;
		if (ig >= ia && ig >= ic && ig >= it)
			return ig;
		return it;
	}
	
	else
		return 0;
}




/******************************************************************************
 * open_file
 * Abre um arquivo de texto e retorna o ponteiro para ele.
 ******************************************************************************/
FILE * open_file (char *file, char *mode)
{
	FILE *fp;
	
	if ((fp = fopen(file, mode)) == NULL)
	{
		printf("Erro ao abrir o arquivo %s", file);
		exit(0);
	}
	return fp;
}




/******************************************************************************
 * numero_entradas
 * Retorna o numero de entradas contidas na primeira linha do 'dna.in'.
 ******************************************************************************/
int numero_entradas ()
{
	FILE *fp;
	char linha[10];
	
	fp = open_file (ENTRADA, "r");	
	fgets(linha, 10, fp);
	
	return atoi(linha);	
}




/******************************************************************************
 * read_line
 * Retorna a linha indicada.
 ******************************************************************************/
char * read_line (int n)
{
	FILE *fp;
	char value[MAX], linha[MAX], *line, k;
	int  i = 0;
	
	line = (char *) malloc(sizeof(char) * MAX);
	fp = open_file(ENTRADA, "r");
	n -= 1;
	
	strcpy(linha, "");
	
	do
	{
		k = fgetc(fp);
		if (k == '\n')
		{
			i++;
			k = fgetc(fp);
		}
		
		if (i == n)
		{
			sprintf(value, "%c", k);
			strcat(linha, value);
		}
	} while (k != EOF);

	fclose(fp);
	strcpy(line, linha);
	return line;
}



/******************************************************************************
 * Bloco principal
 ******************************************************************************/
int main (int argc, char *argv[])
{
	DNA *tree;
	FILE *f_out;
	int n_lines, i, n;
	char *line1, *line2;
	
	f_out = open_file(SAIDA, "w");
	
	n_lines = 2 * numero_entradas();
	
	for (n = 2; n <= n_lines; n = n + 2)
	{
		line1 = read_line(n);
		line2 = read_line(n + 1);
	
		tree = cria_no();
		
		for (i = 0; line1[i] != '\0'; i++)
			insere(&tree, line1, i);
	
		for (i = 0; line2[i] != '\0'; i++)
			confere(&tree, line2, i);
		
		fprintf(f_out, "%d\n", tamanho(tree));
		free(tree);
	}
	fclose(f_out);
		
	return 0;
}
