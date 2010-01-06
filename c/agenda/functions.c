//------------------------------------------------------------------------------
// FUNCTIONS.C
// Biblioteca para as funções adicionais do programa.
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

//------------------------------------------------------------------------------
// Remove o caracter de nova linha no final de uma string
//------------------------------------------------------------------------------
char *remove_line(const char *string) {
     char *token;
     
     token = (char *) strtok(string, "\n");
     return token;         
}


//------------------------------------------------------------------------------
// Aloca na memória uma string
//------------------------------------------------------------------------------
char *string_aloca(const char *texto) {
     char *str;
     
     if ((str = (char*) malloc(sizeof(char) * strlen(texto))) == NULL)
        exit(1);
                 //buffer_escreve("Erro ao alocar memoria para a string!");
     strcpy(str, texto);
     
     return str;
}


//------------------------------------------------------------------------------
// Converte uma string para Uppercase
//------------------------------------------------------------------------------
char *string_up(char *str) {
     char *up = str;
     while (*up) {
           *up = toupper(*up);
           up++;
     }
	return str;
}


//------------------------------------------------------------------------------
// Verifica a extensao do arquivo
//------------------------------------------------------------------------------
int string_ext(char nome[], char ext[]) {
     int i, j;
     char res[4];
     
     for (i = (strlen(nome) - 3), j = 0; i <= strlen(nome); i++, j++)
         res[j] = nome[i];
     
     return (stricmp(res,ext) == 0) ? 0 : 1;         
}



//------------------------------------------------------------------------------
// Escreve no arquivo CSV
//------------------------------------------------------------------------------
void write_csv(FILE *fp, char *nome, char *curso, char *turno, char *cidade) {
     fprintf(fp, "%s;%s;%s;%s\n", nome, curso, turno, cidade);
}


//------------------------------------------------------------------------------
// Escreve no arquivo de formato próprio
//------------------------------------------------------------------------------
void write_pf(FILE *fp, char *nome, char *curso, char *turno, char *cidade) {
     fprintf(fp, "%s;%s;%s;%s\n", nome, curso, turno, cidade);
}


//------------------------------------------------------------------------------
// Abre um arquivo
//------------------------------------------------------------------------------
FILE *open_file(char *nome_arq) {
     FILE *fp;
       
     if ((fp = fopen(nome_arq,"w")) == NULL) {
        dialog_erro_file();
     }
     return fp;
}
