//------------------------------------------------------------------------------
// INTERFACE.H
// Biblioteca para a criação da interface utilizando GTK+
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

void balancear_arvore(void);
void editar_registro(void);
void clear_tree_view(void);
void print_arvore(void);
void buffer_clear(void);
GtkWidget *create_tree_view(void);
void buffer_escreve(const char *txt);
void show_registros();
void busca_ok();
void novo_registro();
void tree_view_add(gchar *nome, gchar *curso, gchar *turno, gchar *cidade);
void save_csv(GtkWidget *w, GtkFileSelection *fs);
void imprime_arquivo(char *arquivo);
void import_csv(GtkWidget *w, GtkFileSelection *fs);
void tree_selection(GtkTreeSelection *selection, gpointer data);
void remove_nome(void);
void cadastro_clear(void);
void cadastro_add(void);
void imprime_dados(GtkWidget *w, GtkFileSelection *fs);

static void dialog_open();
static void dialog_save();
static void dialog_open_csv();
static void dialog_save_csv();

GtkWidget *create_tela_dados(void);
void create_interface(void);
