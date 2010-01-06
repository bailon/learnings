//------------------------------------------------------------------------------
// INTERFACE.C
// Biblioteca para a criação da interface utilizando GTK+
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <gtk/gtk.h>
#include "registro.h"
#include "functions.h"
#include "interface.h"
#include "dialogs.h"

#define MAX_LINE 1024
#define BUF_SIZE 256
#define LEN 100


// Guarda os dados do ListViewModel
enum {
     COL_NOME,
     COL_CURSO,
     COL_TURNO,
     COL_CIDADE,
     NUM_COLS
};

Registro *reg;
char sel_nome[80];

// Declaracao dos Widgets "universais" -----------------------------------------
GtkWidget *edNome         = NULL; // Entry do Nome
GtkWidget *edCurso        = NULL; // Entry do Curso
GtkWidget *edTurno        = NULL; // Entry do Turno
GtkWidget *edCidade       = NULL; // Entry da Cidade
GtkWidget *buscaEd        = NULL; // Entry da caixa de busca
GtkWidget *btChange       = NULL; // Salvar alterações
GtkWidget *btDelete       = NULL; // Excluir o aluno atual
GtkWidget *optAVL         = NULL; // CheckButton de dizer se usa ou nao AVL

GtkWidget *treeview   = NULL; // O TreeView
GtkTreeStore *tmodel      = NULL; // Model do TreeView
GtkTreeIter *titer        = NULL;
GtkTreeSelection *tselect = NULL;
GtkTextBuffer *textbuf    = NULL; // Buffer de texto



//------------------------------------------------------------------------------
// Balancear a arvore
//------------------------------------------------------------------------------
void balancear_arvore(void) {
     if (reg == NULL) return;
     Registro *aux = reg_cria();
     clear_tree_view();
     
     aux = vetoriza(reg, NULL);
     
     reg = reg_libera(reg);
     reg = bal_avl(aux, reg);
     
     aux = reg_libera(aux);
     dialog_msg_bal();
}

//------------------------------------------------------------------------------
// Balanceia a arvore ao clicar na caixa de selecao
//------------------------------------------------------------------------------
void balancear_arvore_bt(void) {   
     if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(optAVL)) == FALSE)
        return;
     else {
          if (reg == NULL) return;
          Registro *aux = reg_cria();
          clear_tree_view();
     
          aux = vetoriza(reg, NULL);
     
          reg = reg_libera(reg);
          reg = bal_avl(aux, reg);
     
          aux = reg_libera(aux);
          dialog_msg_bal();
     }
}


//------------------------------------------------------------------------------
// Modifica um registro
//------------------------------------------------------------------------------
void editar_registro(void) {
     char nome[LEN], curso[LEN], cidade[LEN], turno[LEN];
     
     if (strcmp(gtk_entry_get_text(GTK_ENTRY(edNome)),"") == 0) {
        dialog_erro_vazio();
        return;
     }
        
     clear_tree_view();
     strcpy(nome  , string_up((char *) gtk_entry_get_text(GTK_ENTRY(edNome))));
     strcpy(curso , gtk_entry_get_text(GTK_ENTRY(edCurso)));
     strcpy(cidade, gtk_entry_get_text(GTK_ENTRY(edCidade)));
     strcpy(turno , gtk_entry_get_text(GTK_ENTRY(edTurno)));       

     if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(optAVL)) == TRUE) {
        reg = remove_avl(reg, sel_nome);
        reg = reg_insere_avl(reg, nome, curso, turno, cidade); 
     }
     else {
         reg = remove_est(reg, sel_nome);
         reg = reg_insere(reg, nome, curso, turno, cidade);
     }       
     
     buffer_escreve("O registro de ");
     buffer_escreve(sel_nome);
     buffer_escreve(" foi editado com sucesso!\n");     
     novo_registro();  
}
     
//------------------------------------------------------------------------------
// Imprime a estrutura da árvore
//------------------------------------------------------------------------------
void print_arvore(void) {
     buffer_clear();
     
     imprime_arvore(reg);
}


//------------------------------------------------------------------------------
// Limpa o conteudo da TreeView
//------------------------------------------------------------------------------
void clear_tree_view(void) {
     gtk_tree_store_clear(GTK_TREE_STORE(tmodel));
}


//------------------------------------------------------------------------------
// Limpa o GtkTextBuffer
//------------------------------------------------------------------------------
void buffer_clear(void) {
       GtkTextIter start, end;
       
       gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(textbuf), &start);
       gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(textbuf), &end );
       gtk_text_buffer_delete(GTK_TEXT_BUFFER(textbuf), &start, &end);
}


//------------------------------------------------------------------------------
// Cria o TreeView
//------------------------------------------------------------------------------
GtkWidget *create_tree_view(void) {
       GtkCellRenderer *renderer;
       GtkTreeModel    *model;
       GtkWidget       *view;
       
       view = gtk_tree_view_new();
       
       // Primeira coluna - Nome
       renderer = gtk_cell_renderer_text_new();
       gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1,
             "Nome", renderer, "text", COL_NOME, NULL);
       
       // Segunda coluna - Curso
       renderer = gtk_cell_renderer_text_new();
       gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1,
             "Curso", renderer, "text", COL_CURSO, NULL);
             
       // Terceira coluna - Turno
       renderer = gtk_cell_renderer_text_new();
       gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1,
             "Turno", renderer, "text", COL_TURNO, NULL);
             
       // Quarta coluna - Cidade
       renderer = gtk_cell_renderer_text_new();
       gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), -1,
             "Cidade", renderer, "text", COL_CIDADE, NULL);
       
       return view;
}


//------------------------------------------------------------------------------
// Escreve um texto no TextBuffer
//------------------------------------------------------------------------------
void buffer_escreve(const char *txt) {
      gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(textbuf), txt, strlen(txt));
}


//------------------------------------------------------------------------------
// Novo registro no cadastro
//------------------------------------------------------------------------------
void novo_registro() {
       // Desabilita os botões de alteraçao de registro
       gtk_widget_set_sensitive(btDelete, FALSE);
       gtk_widget_set_sensitive(btChange, FALSE);
       
       // Limpa os campos
       gtk_entry_set_text(GTK_ENTRY(edNome)  , "");
       gtk_entry_set_text(GTK_ENTRY(edCurso) , "");
       gtk_entry_set_text(GTK_ENTRY(edTurno) , "");
       gtk_entry_set_text(GTK_ENTRY(edCidade), "");
}



//------------------------------------------------------------------------------
// Exibe os registros na TreeView
//------------------------------------------------------------------------------
void show_registros() {
     clear_tree_view();
     imprime_lista(reg);    
}


//------------------------------------------------------------------------------
// Realiza a busca por um registro
//------------------------------------------------------------------------------
void busca_ok() {
     clear_tree_view();
     reg_busca(reg, gtk_entry_get_text(GTK_ENTRY(buscaEd)));
}


//------------------------------------------------------------------------------
// Adicionar item no TreeView
//------------------------------------------------------------------------------
void tree_view_add(gchar *nome, gchar *curso, gchar *turno, gchar *cidade) {
    gtk_tree_store_append(GTK_TREE_STORE(tmodel), &titer, NULL);
    gtk_tree_store_set(GTK_TREE_STORE(tmodel), &titer, 
          COL_NOME, nome,
          COL_CURSO, curso,
          COL_TURNO, turno,
          COL_CIDADE, cidade, -1);
}


//------------------------------------------------------------------------------
// Salva o arquivo no formato CSV
//------------------------------------------------------------------------------
void save_csv(GtkWidget *w, GtkFileSelection *fs) {
     FILE *fp;
     char nome_arquivo[100];
              
     strcpy(nome_arquivo, gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
     
     fp = (FILE *) open_file(nome_arquivo);
     imprime_lista_csv(reg, fp);
     
     fclose(fp);
     gtk_widget_destroy((gpointer)fs);
}


//------------------------------------------------------------------------------
// Salva o arquivo no formato próprio
//------------------------------------------------------------------------------
void save_pf(GtkWidget *w, GtkFileSelection *fs) {
     FILE *fp;
     char nome_arquivo[LEN];
              
     strcpy(nome_arquivo, gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
     
     fp = (FILE *) open_file(nome_arquivo);
     salva_lista_pf(reg, fp);
     
     fclose(fp);
     gtk_widget_destroy((gpointer)fs);
}


//------------------------------------------------------------------------------
// Importa um arquivo CSV
//------------------------------------------------------------------------------
void import_csv(GtkWidget *w, GtkFileSelection *fs) {
       FILE *fp;
       char nome_arquivo[LEN], linha[MAX_LINE], tc[10];
       char *token, nome[LEN], curso[LEN], turno[LEN], cidade[LEN];
       int i, t;
              
       strcpy(nome_arquivo, gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
       
       if (string_ext(nome_arquivo,"csv") != 0) {
          dialog_erro_csv();
       }
       else {
          if ((fp = fopen(nome_arquivo,"r")) == NULL) {
             dialog_erro_file();
             return;
          }
       
          t = 0;
          while (fgets(linha,MAX_LINE,fp)) {
                token = (char*) strtok(linha, ";");
             
                i = 0;
                t++;
                while (token != NULL) {
                         switch(i) {
                                case 0 : strcpy(nome  , token); break;
                                case 1 : strcpy(curso , token); break;
                                case 2 : strcpy(turno , token); break;
                                case 3 : strcpy(cidade, remove_line(token)); break;
                         }
                   
                         i++;
                         token = (char*) strtok(NULL, ";");
                }
                
                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(optAVL)) == TRUE)
                   reg = reg_insere_avl(reg, nome, curso, turno, cidade);
                else
                    reg = reg_insere(reg, nome, curso, turno, cidade);
                             
                buffer_escreve(nome);
                buffer_escreve(" - ");
                buffer_escreve(curso);
                buffer_escreve(" - ");
                buffer_escreve(turno);
                buffer_escreve(" - ");
                buffer_escreve(cidade);
                buffer_escreve("\n");
             }
       
             buffer_escreve("\n--------------------------------------------------\n");
             buffer_escreve("Arquivo CSV importado com sucesso!\n");
             // Converte int para char na base 10
             buffer_escreve(itoa(t,tc,10));
             buffer_escreve(" registros foram importados com sucesso!\n\n");

             fclose(fp);
             }
       gtk_widget_destroy((gpointer)fs);
}



//------------------------------------------------------------------------------
// Importa do formato proprio
//------------------------------------------------------------------------------
void import_fp(GtkWidget *w, GtkFileSelection *fs) {
       FILE *fp;
       char nome_arquivo[LEN], linha[MAX_LINE], tc[10];
       char *token, nome[LEN], curso[LEN], turno[LEN], cidade[LEN];
       int i, t;
              
       strcpy(nome_arquivo, gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
       
       if (string_ext(nome_arquivo,"ted") != 0) {
          dialog_erro_csv();
       }
       else {
          if ((fp = fopen(nome_arquivo,"r")) == NULL) {
             dialog_erro_file();
             return;
          }
       
       
          t = 0;
          while (fgets(linha,MAX_LINE,fp)) {
                token = (char*) strtok(linha, ";");
             
                i = 0;
                t++;
                while (token != NULL) {
                         switch(i) {
                                case 0 : strcpy(nome  , token); break;
                                case 1 : strcpy(curso , token); break;
                                case 2 : strcpy(turno , token); break;
                                case 3 : strcpy(cidade, remove_line(token)); break;
                         }
                   
                         i++;
                         token = (char*) strtok(NULL, ";");
                }
                
                reg = reg_insere(reg, nome, curso, turno, cidade);
             }
       
             buffer_escreve("\n--------------------------------------------------\n");
             buffer_escreve("Arquivo importado com sucesso!\n");

             fclose(fp);
             }
       gtk_widget_destroy((gpointer)fs);
}


//------------------------------------------------------------------------------
// Imprime o item selecionado no TreeView
//------------------------------------------------------------------------------
void tree_selection(GtkTreeSelection *selection, gpointer data) {
        GtkTreeIter iter;
        GtkTreeModel *model;
        gchar *nome, *cidade, *curso, *turno;

        if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
                gtk_tree_model_get(model, &iter, COL_NOME  , &nome  , -1);
                gtk_tree_model_get(model, &iter, COL_CURSO , &curso , -1);
                gtk_tree_model_get(model, &iter, COL_TURNO , &turno , -1);
                gtk_tree_model_get(model, &iter, COL_CIDADE, &cidade, -1);
                
                strcpy(sel_nome, nome);
                
                gtk_entry_set_text(GTK_ENTRY(edNome)  , nome);
                gtk_entry_set_text(GTK_ENTRY(edCurso) , curso);
                gtk_entry_set_text(GTK_ENTRY(edTurno) , turno);
                gtk_entry_set_text(GTK_ENTRY(edCidade), cidade);
                
                // Habilita os botoes do cadastro para poder modificar o
                // cadastro do aluno.
                gtk_widget_set_sensitive(btDelete, TRUE);
                gtk_widget_set_sensitive(btChange, TRUE);
        }
        
        g_free(nome);
        g_free(cidade);
        g_free(curso);
        g_free(turno);
        
        //gtk_widget_destroy((gpointer)selection);
}

//------------------------------------------------------------------------------
// Remove um registro
//------------------------------------------------------------------------------
void remove_nome(void) {     
     clear_tree_view();
     
     if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(optAVL)) == TRUE)
        reg = remove_avl(reg, sel_nome);
     else
         reg = remove_est(reg, sel_nome);
     
     buffer_escreve("O registro de ");
     buffer_escreve(sel_nome);
     buffer_escreve(" foi removido com sucesso!\n");     
     novo_registro();
}



//------------------------------------------------------------------------------
// Limpa os campos do formulário
//------------------------------------------------------------------------------
void cadastro_clear(void) {
       gtk_entry_set_text(GTK_ENTRY(edNome), "");
       gtk_entry_set_text(GTK_ENTRY(edCurso), "");
       gtk_entry_set_text(GTK_ENTRY(edTurno), "");
       gtk_entry_set_text(GTK_ENTRY(edCidade), "");
}

//------------------------------------------------------------------------------
// Captura os dados do cadastro
//------------------------------------------------------------------------------
void cadastro_add(void) {  
       char nome[LEN], curso[LEN], cidade[LEN], turno[LEN];
       
       
       if (strcmp(gtk_entry_get_text(GTK_ENTRY(edNome)),"") == 0) {
        dialog_erro_vazio();
        return;
     }
     
       clear_tree_view();
       strcpy(nome  , string_up((char *) gtk_entry_get_text(GTK_ENTRY(edNome))));
       strcpy(curso , gtk_entry_get_text(GTK_ENTRY(edCurso)));
       strcpy(cidade, gtk_entry_get_text(GTK_ENTRY(edCidade)));
       strcpy(turno , gtk_entry_get_text(GTK_ENTRY(edTurno)));
       
       if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(optAVL)) == TRUE)
          reg = reg_insere_avl(reg, nome, curso, turno, cidade);
       else
           reg = reg_insere(reg, nome, curso, turno, cidade);
       
       buffer_escreve("Registro adicionado:\n");
       buffer_escreve(nome);
       buffer_escreve(" - ");
       buffer_escreve(curso);
       buffer_escreve(" - ");
       buffer_escreve(turno);
       buffer_escreve(" - ");
       buffer_escreve(cidade);
       buffer_escreve("\n");
       
       // Limpa o conteudo dos EDITS
       gtk_entry_set_text(GTK_ENTRY(edNome),  "");
       gtk_entry_set_text(GTK_ENTRY(edCurso), "");
       gtk_entry_set_text(GTK_ENTRY(edTurno), "");
       gtk_entry_set_text(GTK_ENTRY(edCidade),"");
}


//------------------------------------------------------------------------------
// Dialog de abrir arquivo
//------------------------------------------------------------------------------
void dialog_open() {
       GtkWidget *fs;
       fs = gtk_file_selection_new ("Abrir Arquivo");

       g_signal_connect(G_OBJECT(fs), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);
       g_signal_connect(G_OBJECT(GTK_FILE_SELECTION (fs)->ok_button), "clicked", 
           G_CALLBACK (import_fp), (gpointer) fs);
       g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (fs)->cancel_button), 
           "clicked", G_CALLBACK (gtk_widget_destroy), G_OBJECT(fs));
       
       gtk_widget_show(fs);
}



//------------------------------------------------------------------------------
// Dialog de salvar arquivo
//------------------------------------------------------------------------------
void dialog_save_pf() {
       GtkWidget *fs;
       fs = gtk_file_selection_new ("Salvar Arquivo");

       g_signal_connect(G_OBJECT(fs), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);
       g_signal_connect(G_OBJECT(GTK_FILE_SELECTION (fs)->ok_button), "clicked", 
           G_CALLBACK (save_pf), (gpointer) fs);
       g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (fs)->cancel_button), 
           "clicked", G_CALLBACK (gtk_widget_destroy), G_OBJECT(fs));
       
       gtk_widget_show(fs);
}

//------------------------------------------------------------------------------
// Dialog de abrir arquivo CSV
//------------------------------------------------------------------------------
void dialog_open_csv() {
       GtkWidget *fs;
       fs = gtk_file_selection_new("Importar de arquivo CSV");
       
       // --- Signals da dialog
       g_signal_connect(G_OBJECT(fs), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);
       g_signal_connect(G_OBJECT(GTK_FILE_SELECTION (fs)->ok_button), "clicked", 
           G_CALLBACK (import_csv), (gpointer) fs);
       g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (fs)->cancel_button), 
           "clicked", G_CALLBACK (gtk_widget_destroy), G_OBJECT(fs));
       
       gtk_widget_show(fs);
}


//------------------------------------------------------------------------------
// Dialog de salvar arquivo
//------------------------------------------------------------------------------
void dialog_save_csv() {
       GtkWidget *fs;
       fs = gtk_file_selection_new ("Exportar para arquivo CSV");

       g_signal_connect(G_OBJECT(fs), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);
       g_signal_connect(G_OBJECT(GTK_FILE_SELECTION (fs)->ok_button), "clicked", 
           G_CALLBACK (save_csv), (gpointer) fs);
       g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (fs)->cancel_button), 
           "clicked", G_CALLBACK (gtk_widget_destroy), G_OBJECT(fs));
       
       gtk_widget_show(fs);
}

//------------------------------------------------------------------------------
// Cria a tela de inserção e edição de registros
//------------------------------------------------------------------------------
GtkWidget *create_tela_dados(void) {
       GtkWidget *table    = NULL; 
       GtkWidget *lbNome   = NULL;
       GtkWidget *lbCurso  = NULL;
       GtkWidget *lbTurno  = NULL;
       GtkWidget *lbCidade = NULL;
       GtkWidget *noteBB   = NULL;
       GtkWidget *box      = NULL;
       GtkWidget *box2     = NULL;
       GtkWidget *btClear  = NULL;   // Limpar dados do formulário
       GtkWidget *btAdd    = NULL;   // Adicionar cadastro no formulário
       GtkWidget *btNew    = NULL;
       
       // Cria as boxes
       box     = gtk_vbox_new(FALSE, 4);
       noteBB  = gtk_hbox_new(FALSE, 4);
       box2    = gtk_hbox_new(FALSE, 4);
       gtk_box_set_spacing(GTK_BOX(noteBB), 2);
       gtk_box_set_spacing(GTK_BOX(box2), 2);
       
       // Cria a tabela
       table = gtk_table_new(4, 2, FALSE);
       gtk_table_set_col_spacings(GTK_TABLE(table), 4);
       gtk_table_set_row_spacings(GTK_TABLE(table), 4);
       
       // Labels do cadastro
       lbNome    = gtk_label_new("Nome: ");
       lbCurso   = gtk_label_new("Curso: ");
       lbTurno   = gtk_label_new("Turno: ");
       lbCidade  = gtk_label_new("Cidade: ");
       
       // Campos do cadastro
       edNome    = gtk_entry_new_with_max_length(50);
       edCurso   = gtk_entry_new_with_max_length(30);
       edTurno   = gtk_entry_new_with_max_length(20);
       edCidade  = gtk_entry_new_with_max_length(50);
       
       // Botoes do cadastro
       btAdd     = gtk_button_new_with_label("Cadastrar");
       btClear   = gtk_button_new_with_label("Limpar");
       btNew     = gtk_button_new_with_label("Novo Registro");
       btDelete  = gtk_button_new_with_label("Excluir");
       btChange  = gtk_button_new_with_label("Salvar Modificacoes");
       
       gtk_widget_set_sensitive(btDelete, FALSE);
       gtk_widget_set_sensitive(btChange, FALSE);
       
       
       // Empacotando...
       gtk_box_pack_start(GTK_BOX(noteBB), btClear, TRUE, TRUE, TRUE);
       gtk_box_pack_start(GTK_BOX(noteBB), btAdd, TRUE, TRUE, TRUE);
       
       gtk_box_pack_start(GTK_BOX(box2), btNew,    TRUE, TRUE, TRUE);
       gtk_box_pack_start(GTK_BOX(box2), btChange, TRUE, TRUE, TRUE);
       gtk_box_pack_start(GTK_BOX(box2), btDelete, TRUE, TRUE, TRUE);
       
       // Inserindo componentes na tabela de cadastro
       gtk_table_attach_defaults(GTK_TABLE(table), lbNome  , 0, 1, 0, 1);
       gtk_table_attach_defaults(GTK_TABLE(table), lbCurso , 0, 1, 1, 2);
       gtk_table_attach_defaults(GTK_TABLE(table), lbTurno , 0, 1, 2, 3);
       gtk_table_attach_defaults(GTK_TABLE(table), lbCidade, 0, 1, 3, 4);
       gtk_table_attach_defaults(GTK_TABLE(table), edNome  , 1, 2, 0, 1);
       gtk_table_attach_defaults(GTK_TABLE(table), edCurso , 1, 2, 1, 2);
       gtk_table_attach_defaults(GTK_TABLE(table), edTurno , 1, 2, 2, 3);
       gtk_table_attach_defaults(GTK_TABLE(table), edCidade, 1, 2, 3, 4);
       
       gtk_box_pack_start(GTK_BOX(box), table , FALSE, TRUE, TRUE);
       gtk_box_pack_start(GTK_BOX(box), noteBB, FALSE, TRUE, FALSE);
       gtk_box_pack_start(GTK_BOX(box), box2  , FALSE, TRUE, FALSE);
       
       g_signal_connect(G_OBJECT(btAdd)   , "clicked", G_CALLBACK(cadastro_add), NULL);
       g_signal_connect(G_OBJECT(btClear) , "clicked", G_CALLBACK(cadastro_clear), NULL);
       g_signal_connect(G_OBJECT(btNew)   , "clicked", G_CALLBACK(novo_registro), NULL);
       g_signal_connect(G_OBJECT(btDelete), "clicked", G_CALLBACK(remove_nome), NULL);
       g_signal_connect(G_OBJECT(btChange), "clicked", G_CALLBACK(editar_registro), NULL);
       
       return box;
}



//------------------------------------------------------------------------------
// DESENHA A INTERFACE GRAFICA
//------------------------------------------------------------------------------
void create_interface(void) {
       // ----- Declaracao dos Widgets -----------------------------------------
       GtkWidget *win    = NULL;  // Janela principal
       // Containers
       GtkWidget *hbox   = NULL;
       GtkWidget *vbox   = NULL;
       
       // Notebook
       GtkWidget *notebook   = NULL;
       GtkWidget *noteL1     = NULL; // Label da primeira página
       GtkWidget *noteL2     = NULL; // Label da segunda página
       GtkWidget *noteL3     = NULL; // Label da terceira página
       GtkWidget *noteB1     = NULL; // Box da primeira página
       GtkWidget *noteB2     = NULL; // Box da segunda página
       GtkWidget *noteB3     = NULL; // Box da terceira página
       
       // Botoes da interface
       GtkWidget *btSave   = NULL;   // Salvar
       GtkWidget *btOpen   = NULL;   // Abrir
       GtkWidget *btImpCSV = NULL;   // Importar arquivo CSV
       GtkWidget *btExpCSV = NULL;   // Exportar arquivo CSV
       GtkWidget *btBal    = NULL;   // Balancear a árvore
       GtkWidget *btShow   = NULL;   // Exibir a estrutura da árvore
       GtkWidget *btList   = NULL;   // Listar os nomes na TreeView
           
       GtkWidget *scroll   = NULL;   // Scroll do GtkTextView
       GtkWidget *hline1   = NULL;   // Separador horizontal 1
       GtkWidget *hline2   = NULL;   // Separador horizontal 2
       GtkWidget *hline3   = NULL;   // Separador horizontal 3
       
       GtkWidget *tscroll    = NULL; // Barra de rolagem para o TreeView
       GtkWidget *textbox    = NULL;
       
       GtkWidget *buscaBt    = NULL; // Botão da caixa de busca
       GtkWidget *buscaHBox  = NULL; // Box horizontal da busca
       GtkWidget *buscaHLine = NULL; // Linha separadora da busca
       
       GtkWidget *cadastro   = NULL; // Tela de cadastro
       
       
       
      
     
       // ----- Criacao da janela principal ------------------------------------
       win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
       gtk_container_set_border_width (GTK_CONTAINER (win), 4);
       gtk_window_set_title(GTK_WINDOW (win), "UFPel - Controle de Matriculas");
       gtk_window_set_position(GTK_WINDOW (win), GTK_WIN_POS_CENTER);
       gtk_window_set_default_size(GTK_WINDOW (win), 720, 400);
       
       
       
       // ----- Criacao dos Widgets na Interface -------------------------------
       // HBOX e VBOX
       hbox = gtk_hbox_new(FALSE, 4);
       gtk_container_add(GTK_CONTAINER(win), hbox);
       
       vbox = gtk_vbox_new(FALSE, 2);
       
       // Botoes
       btOpen    = gtk_button_new_with_label("Abrir Arquivo");
       btSave    = gtk_button_new_with_label("Salvar Arquivo");
       btImpCSV  = gtk_button_new_with_label("Importar CSV");
       btExpCSV  = gtk_button_new_with_label("Exportar CSV");
       btBal     = gtk_button_new_with_label("Balancear Arvore");
       btShow    = gtk_button_new_with_label("Exibir Estrutura");
       
       
       // Frame de opções
       optAVL = gtk_check_button_new_with_label("Utilizar AVL");
       
       // Separador horizontl
       hline1 = gtk_hseparator_new();
       hline2 = gtk_hseparator_new();
       hline3 = gtk_hseparator_new();      
       
       // Packing!        
       gtk_box_pack_start(GTK_BOX(hbox),  vbox     , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  btOpen   , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  btSave   , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  hline1   , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  btImpCSV , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  btExpCSV , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  hline2   , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  btBal    , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  btShow   , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  hline3   , FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(vbox),  optAVL   , FALSE, FALSE, TRUE);
       gtk_container_set_border_width(GTK_CONTAINER(vbox), 2);
       
         
       
       // Notebook -------------------------------------------------------------
       notebook = gtk_notebook_new();
       gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
       
       // --- Cria os labels
       noteL1 = gtk_label_new("Log");
       noteL2 = gtk_label_new("Cadastrar Aluno");
       noteL3 = gtk_label_new("Busca");
       
       // --- Cria os boxes
       noteB1 = gtk_vbox_new(FALSE, 8);
       noteB2 = gtk_vbox_new(FALSE, 8);
       noteB3 = gtk_vbox_new(FALSE, 8);
       
       gtk_box_set_spacing(GTK_BOX(noteB1), 8); 
       gtk_box_set_spacing(GTK_BOX(noteB2), 8);
       gtk_box_set_spacing(GTK_BOX(noteB3), 8);
       
       gtk_notebook_append_page(GTK_NOTEBOOK(notebook), noteB3, noteL3);
       gtk_notebook_append_page(GTK_NOTEBOOK(notebook), noteB2, noteL2);
       gtk_notebook_append_page(GTK_NOTEBOOK(notebook), noteB1, noteL1);
       
       gtk_box_pack_start(GTK_BOX(hbox),  notebook, TRUE, TRUE, TRUE);
       gtk_container_set_border_width (GTK_CONTAINER(noteB2), 4);
       
       // Cria a tela de cadastro
       cadastro = create_tela_dados();
       gtk_box_pack_start(GTK_BOX(noteB2), cadastro, FALSE, TRUE, FALSE);
       
       // ----- Textbox --------------------------------------------------------
       textbox = gtk_text_view_new();
       textbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textbox));
       
       scroll = gtk_scrolled_window_new(NULL, NULL);
       gtk_container_set_border_width (GTK_CONTAINER(scroll), 4);
       gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), textbox);
       
       gtk_text_view_set_editable(GTK_TEXT_VIEW(textbox), FALSE);       
       gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbox), FALSE);
       gtk_box_pack_start(GTK_BOX(noteB1), scroll, TRUE, TRUE, TRUE);
       
       // ----- Frame de Busca -------------------------------------------------
       buscaEd    = gtk_entry_new_with_max_length(80);
       buscaBt    = gtk_button_new_with_label("OK");
       btList    = gtk_button_new_with_label("Listar Registros");
       buscaHBox  = gtk_hbox_new(TRUE,4);
       buscaHLine = gtk_hseparator_new();
       
       gtk_box_pack_start(GTK_BOX(buscaHBox), buscaEd, TRUE, TRUE, TRUE);
       gtk_box_pack_start(GTK_BOX(buscaHBox), buscaBt, TRUE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(buscaHBox), btList, TRUE, FALSE, TRUE);
       
       // ----- TreeView -------------------------------------------------------
       treeview = create_tree_view();
       tmodel   = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
       gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(tmodel));
       
       tselect = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
       gtk_tree_selection_set_mode(tselect, GTK_SELECTION_SINGLE);
       g_signal_connect(G_OBJECT(tselect), "changed", G_CALLBACK(tree_selection), NULL);
       
       tscroll = gtk_scrolled_window_new(NULL, NULL);
       gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(tscroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(tscroll), treeview);
       
       gtk_container_set_border_width(GTK_CONTAINER(noteB3), 4);
       gtk_box_pack_start(GTK_BOX(noteB3), buscaHBox, FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(noteB3), buscaHLine, FALSE, FALSE, TRUE);
       gtk_box_pack_start(GTK_BOX(noteB3), tscroll, TRUE, TRUE, TRUE);
       
       
       // ----- Signals --------------------------------------------------------  
       g_signal_connect(win, "delete_event", GTK_SIGNAL_FUNC(confirma_saida), NULL);  
       g_signal_connect(G_OBJECT(btOpen)   , "clicked", G_CALLBACK(dialog_open), NULL);
       g_signal_connect(G_OBJECT(btSave)   , "clicked", G_CALLBACK(dialog_save_pf), NULL);
       g_signal_connect(G_OBJECT(btImpCSV) , "clicked", G_CALLBACK(dialog_open_csv), NULL);
       g_signal_connect(G_OBJECT(btExpCSV) , "clicked", G_CALLBACK(dialog_save_csv), NULL);
       g_signal_connect(G_OBJECT(btBal)    , "clicked", G_CALLBACK(balancear_arvore), NULL);
       g_signal_connect(G_OBJECT(btShow)   , "clicked", G_CALLBACK(print_arvore), NULL);
       g_signal_connect(G_OBJECT(btList)   , "clicked", G_CALLBACK(show_registros), NULL);
       g_signal_connect(G_OBJECT(buscaBt)  , "clicked", G_CALLBACK(busca_ok), NULL);
       g_signal_connect(G_OBJECT(optAVL)   , "clicked", G_CALLBACK(balancear_arvore_bt), NULL);
       
       reg = reg_vazio();
       
       // ----- Exibe a interface ----------------------------------------------
       gtk_widget_show_all(win);
}
