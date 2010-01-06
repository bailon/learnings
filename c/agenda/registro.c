//------------------------------------------------------------------------------
// REGISTRO.C
// Biblioteca de funções para manipulação de árvores binárias estáticas e AVL,
// operando sobre uma lista de registros.
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
#include "dialogs.h"

#define MAX 100

//------------------------------------------------------------------------------
// Definição da struct que armazena os registros
//------------------------------------------------------------------------------
struct registro {
	char nome[MAX];
	char curso[MAX];
	char turno[MAX];
	char cidade[MAX];

	int fb;
	struct registro *pai;
	struct registro *esq;
	struct registro *dir;
};



//------------------------------------------------------------------------------
// REG_VAZIO
//   Cria um registro vazio
//------------------------------------------------------------------------------
Registro *reg_vazio() {
	return NULL;
}



//------------------------------------------------------------------------------
// REG_CRIA
//   Cria um novo registro na memória
//------------------------------------------------------------------------------
Registro *reg_cria() {
	Registro *reg = malloc(sizeof(Registro));

	if (reg == NULL) {
		//printf("Memoria insuficiente");
		//system("Pause");
		//exit(1);
	}

	reg->esq = NULL;
	reg->dir = NULL;
	return reg;
}



//------------------------------------------------------------------------------
// REG_LIBERA
//   Libera a memória alocada pelo registro e todos os nós abaixo
//------------------------------------------------------------------------------
Registro *reg_libera(Registro *reg) {
	if (reg->esq != NULL)
		reg->esq = reg_libera(reg->esq);

	if (reg->dir != NULL)
		reg->dir = reg_libera(reg->dir);

	free(reg);
	return NULL;
}



//------------------------------------------------------------------------------
// REG_BUSCA
//   Busca um registro pelo seu nome
//------------------------------------------------------------------------------
void *reg_busca(Registro *reg, const char *nome) {
	if (reg == NULL) {
		dialog_erro_busca();
		return;
	}
	
	if (stricmp(reg->nome, nome) == 0) {
		tree_view_add(reg->nome, reg->curso, reg->turno, reg->cidade);
		return;
	}
	
	if (stricmp(reg->nome, nome) > 0) reg_busca(reg->esq, nome);
	if (stricmp(reg->nome, nome) < 0) reg_busca(reg->dir, nome);
}



//------------------------------------------------------------------------------
// REG_INSERE
//   Insere um novo registro, preenchendo os dados e o colocando em sua
//   posição correta dentro da árvore binária
//------------------------------------------------------------------------------
Registro *reg_insere(Registro *reg, const char *nome, const char *curso, const char *turno, const char *cidade) {
	if (reg == NULL) {
		reg = reg_cria();
		strcpy(reg->nome  , nome);
		strcpy(reg->curso , curso);
		strcpy(reg->turno , turno);
		strcpy(reg->cidade, cidade);
		reg->fb=0;
	}
	
	if (stricmp(reg->nome, nome) > 0) {
		Registro *aux = reg_insere(reg->esq, nome, curso, turno, cidade);
		reg->esq = aux;
		reg->esq->pai = reg;
	}
	
	if (stricmp(reg->nome, nome) < 0) {
		Registro *aux = reg_insere(reg->dir, nome, curso, turno, cidade);
		reg->dir = aux;
		reg->dir->pai = reg;
	}
	return reg;
}



//------------------------------------------------------------------------------
// REG_INSERE_AVL
//   Insere um novo registro, preenchendo os dados e o colocando em sua
//   posição correta dentro da árvore binária e checa o balanceamento da
//   mesma. Caso esteje balanceada, reorganiza os nós.
//------------------------------------------------------------------------------
Registro *reg_insere_avl(Registro *reg, const char *nome, const char *curso, const char *turno, const char *cidade) {
	if (reg == NULL) {
		reg = reg_cria();
		strcpy(reg->nome  , nome);
		strcpy(reg->curso , curso);
		strcpy(reg->turno , turno);
		strcpy(reg->cidade, cidade);
		reg->fb = 0;
	}
	
	if (strcmp(reg->nome, nome) > 0) {
		Registro *aux = reg_insere_avl(reg->esq, nome, curso, turno, cidade);
		reg->esq = aux;
		reg->esq->pai = reg;
	}
	
	if (strcmp(reg->nome, nome) < 0) {
		Registro *aux = reg_insere_avl(reg->dir, nome, curso, turno, cidade);
		reg->dir = aux;
		reg->dir->pai = reg;
	}
	
	reg->fb = fator_bal(reg);
	
	if (reg->fb >= 2) {
		if (reg->dir->dir != NULL) reg=rot_esq(reg);
		else reg = rot_dir_esq(reg);
		reg->fb = fator_bal(reg);
	}
	
	if (reg->fb <= -2) {
		if (reg->esq->esq != NULL) reg = rot_dir(reg);
		else reg = rot_esq_dir(reg);
		reg->fb = fator_bal(reg);
	}
	return reg;
}



//------------------------------------------------------------------------------
// ALTURA
//   Retorna a altura de um nó
//------------------------------------------------------------------------------
int altura(Registro *reg) {
	if (reg == NULL) return 0;
	
	int esq = altura(reg->esq);
	int dir = altura(reg->dir);
	
	return (esq >= dir)? esq + 1 : dir + 1;
}



//------------------------------------------------------------------------------
// FATOR_BAL
//   Calcula o fator de balanceamento de um nó
//------------------------------------------------------------------------------
int fator_bal(Registro *reg) {
	return altura(reg->dir) - altura(reg->esq);
}



//------------------------------------------------------------------------------
// ROT_ESQ
//   Realiza a rotação esquerda de um nó na árvore
//------------------------------------------------------------------------------
Registro *rot_esq(Registro *no) {
	Registro *temp;
	
	temp = no->dir;
	no->dir = temp->esq; 
	if (temp->esq != NULL) 
		temp->esq->pai = no;
	temp->esq = no;
	temp->pai = no->pai;
	no->pai = temp;
	
	return temp;
}



//------------------------------------------------------------------------------
// ROT_DIR
//   Realiza a rotação direita de um nó na árvore
//------------------------------------------------------------------------------
Registro *rot_dir(Registro *no) {
	Registro *temp;

	temp = no->esq;
	no->esq = temp->dir;
	if (temp->dir != NULL)
	temp->dir->pai = no;
	temp->dir = no;
	temp->pai = no->pai;
	no->pai = temp;

	return temp;
}



//------------------------------------------------------------------------------
// ROT_ESQ_DIR
//   Realiza a rotação esquerda e direita de um nó
//------------------------------------------------------------------------------
Registro *rot_esq_dir(Registro *no) {
	Registro *pai;
	Registro *no_esq;
	Registro *novo_no;

	pai		= no->pai;
	no_esq	= no->esq;
	no->esq = rot_esq(no_esq);
	no_esq	= no->esq;
	novo_no = rot_dir(no);
	novo_no->pai = pai;

return novo_no;
}



//------------------------------------------------------------------------------
// ROT_DIR_ESQ
//   Realiza a rotação direita e esquerda de um nó
//------------------------------------------------------------------------------
Registro *rot_dir_esq(Registro *no) {
	Registro *pai;
	Registro *no_dir;
	Registro *novo_no;

	pai 	= no->pai;
	no_dir 	= no->dir;
	no->dir = rot_dir(no_dir);
	no_dir 	= no->dir;
	novo_no = rot_esq(no);
	novo_no->pai = pai;

	return novo_no;
}



//------------------------------------------------------------------------------
// IMPRIME_LISTA
//   Imprime os dados da árvore binária ordenadamente
//------------------------------------------------------------------------------
void imprime_lista(Registro *reg) {
	if (reg==NULL) return;
	
	if (reg->esq != NULL) imprime_lista(reg->esq);
	tree_view_add(reg->nome, reg->curso, reg->turno, reg->cidade);
	if (reg->dir != NULL) imprime_lista(reg->dir);
}


//------------------------------------------------------------------------------
// IMPRIME_LISTA_CSV
//   Imprime a lista no formato CSV
//------------------------------------------------------------------------------
void imprime_lista_csv(Registro *reg, FILE *fp) {
	if (reg == NULL) return;
	
	if (reg->esq != NULL) imprime_lista_csv(reg->esq, fp);
	write_csv(fp, reg->nome, reg->curso, reg->turno, reg->cidade);
	if (reg->dir != NULL) imprime_lista_csv(reg->dir, fp);
}

//------------------------------------------------------------------------------
// SALVA_LISTA_PF
//   Imprime a lista no formato CSV
//------------------------------------------------------------------------------
void salva_lista_pf(Registro *reg, FILE *fp) {
	if (reg == NULL) return;
	
	write_pf(fp, reg->nome, reg->curso, reg->turno, reg->cidade);
	if (reg->esq != NULL) salva_lista_pf(reg->esq, fp);
	if (reg->dir != NULL) salva_lista_pf(reg->dir, fp);
}


//------------------------------------------------------------------------------
// IMPRIME_ARVORE
//   Imprime a estrutura da árvore binária, como os nós estão colocados
//------------------------------------------------------------------------------
void imprime_arvore(Registro *reg) {
	if (reg == NULL) return;

	static int tab = 0;
	
	if (reg->dir != NULL) {
		tab++;
		imprime_arvore(reg->dir);
		tab--;
	}
	
	espaco(tab);
	
	buffer_escreve(reg->nome);
	buffer_escreve("\n");
	
	if (reg->esq != NULL) {
		tab++;
		imprime_arvore(reg->esq);
		tab--;
	}
}



//------------------------------------------------------------------------------
// ESPACO
//   Adiciona os espacos na impressão da estrutura da árvore binária
//------------------------------------------------------------------------------
int espaco(int tab) {
	for( ; tab > 0; tab--) buffer_escreve("\t");
}



//------------------------------------------------------------------------------
// REMOVE_EST
//   Remove estáticamente um registro da árvore binária
//------------------------------------------------------------------------------
Registro *remove_est(Registro *reg, const char *nome) {
	if (reg == NULL) return NULL;
	
	if (stricmp(reg->nome, nome) == 0) {
		if ((reg->esq == NULL) && (reg->dir == NULL)) {
			free(reg);
			return NULL;
		}
		
		if (reg->dir == NULL) {
			Registro *aux = reg->esq;
			free(reg);
			return aux;
		}
		
		if (reg->esq == NULL) {
			Registro *aux = reg->dir;
			free(reg);
			return aux;
		}
		
		Registro *aux  = reg->esq;
		Registro *aux2 = reg->esq;
		
		for( ; aux2->dir != NULL; aux2 = aux2->dir);
		aux2->dir = reg->dir;
		free(reg);
		return aux;
	}
	
	if (stricmp(reg->nome, nome) > 0) reg->esq = remove_est(reg->esq, nome);
	if (stricmp(reg->nome, nome) < 0) reg->dir = remove_est(reg->dir, nome);
	return reg;
}



//------------------------------------------------------------------------------
// REMOVE_AVL
//   Remove um registro e balanceia a árvore caso necessário
//------------------------------------------------------------------------------
Registro *remove_avl(Registro *reg,  const char *nome) {
	if (reg == NULL) return NULL;
	if (stricmp(reg->nome, nome) == 0) {
		if ((reg->esq) == NULL && (reg->dir == NULL)) {
			free(reg);
			return NULL;
		}
		
		if (reg->dir == NULL) {
			Registro *aux = reg->esq;
			free(reg);
			aux->fb = fator_bal(aux);
			return aux;
		}
		
		if (reg->esq == NULL) {
			Registro *aux = reg->dir;
			free(reg);
			aux->fb = fator_bal(aux);
			return aux;
		}
		
		Registro *aux  = reg->esq;
		Registro *aux2 = reg->esq;
		
		for ( ; aux2->dir != NULL; aux2 = aux2->dir);
		aux2->dir=reg->dir;
		free(reg);
		aux->fb=fator_bal(aux);
		
		if (aux->fb >= 2) {
			if (aux->dir->dir != NULL) aux=rot_esq(aux);
			else rot_dir_esq(aux);
			aux->fb = fator_bal(aux);
		}

		if (aux->fb <= -2) {
			if (aux->esq->esq != NULL) aux = rot_dir(reg);
			else rot_esq_dir(aux);
			aux->fb = fator_bal(aux);
		}
		
		return aux;
	}
	
	if (stricmp(reg->nome, nome) > 0) reg->esq = remove_avl(reg->esq, nome);
	if (stricmp(reg->nome, nome) < 0) reg->dir = remove_avl(reg->dir, nome);
	return reg;
}



//------------------------------------------------------------------------------
// VETORIZA
//   Cria uma lista encadeada dos registros da árvore binária
//------------------------------------------------------------------------------
Registro *vetoriza(Registro *reg, Registro *aux) {
	if (reg == NULL) return NULL;
	if (reg->esq != NULL) aux = vetoriza(reg->esq, aux);
	aux = reg_insere(aux, reg->nome, reg->curso, reg->turno, reg->cidade);
	if (reg->dir != NULL) aux = vetoriza(reg->dir, aux);
	
	return aux;
}



//------------------------------------------------------------------------------
// BAL_AVL
//   Realiza o balanceamento AVL da árvore binária
//------------------------------------------------------------------------------
Registro *bal_avl(Registro *reg, Registro *bal) {
         if (reg == NULL) return NULL;
	for ( ; reg != NULL; reg = reg->dir)
		bal = reg_insere_avl(bal, reg->nome, reg->curso, reg->turno, reg->cidade);
	
	return bal;
}
