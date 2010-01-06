//------------------------------------------------------------------------------
// REGISTRO.H
// Biblioteca de funções para manipulação de árvores binárias estáticas e AVL,
// operando sobre uma lista de registros.
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

typedef struct registro Registro;

Registro *reg_vazio();
Registro *reg_cria();
Registro *reg_libera(Registro *reg);
void *reg_busca(Registro *reg, const char *nome);
Registro *reg_insere_avl(Registro *reg, const char *nome, const char *curso, const char *turno, const char *cidade);
Registro *reg_insere(Registro *reg, const char *nome, const char *curso, const char *turno, const char *cidade);
int altura(Registro *reg);
int fator_bal(Registro *reg);
Registro *rot_dir(Registro *reg);
Registro *rot_esq(Registro *reg);
Registro *rot_dir_esq(Registro *no);
Registro *rot_esq_dir(Registro *no);
void imprime_arvore(Registro *reg);
void imprime_lista(Registro *reg);
void imprime_lista_csv(Registro *reg, FILE *fp);
void salva_lista_pf(Registro *reg, FILE *fp);
int espaco(int tab);
Registro *remove_est(Registro *reg, const char *nome);
Registro *remove_avl(Registro *reg, const char *nome);
Registro *vetoriza(Registro *reg, Registro *aux);
Registro *bal_avl(Registro *reg, Registro *bal);
