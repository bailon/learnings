//------------------------------------------------------------------------------
// FUNCTIONS.H
// Biblioteca para as funções adicionais do programa.
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

char *remove_line(const char *string);
char *string_aloca(const char *texto);
char *string_up(char *str);
int string_ext(char nome[], char ext[]);
void write_csv(FILE *fp, char *nome, char *curso, char *turno, char *cidade);
void write_pf(FILE *fp, char *nome, char *curso, char *turno, char *cidade);
FILE *open_csv(char *nome_arq);
