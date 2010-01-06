//------------------------------------------------------------------------------
// DIALOGS.C
// Dialogs de mensagens do programa.
//
// Criado por: Bruno Rodrigues      <bruno.ufpel at gmail.com>
//             Guilherme Patzer     <guilermerpatzer at gmail.com>
//
// Data final: 10 de Agosto de 2007
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <gtk/gtk.h>
#include "dialogs.h"

//------------------------------------------------------------------------------
// Dialog padrao informando o erro
//------------------------------------------------------------------------------
void dialog_erro(char msg[]) {
       GtkWidget *dialog = NULL;
       GtkWidget *texto  = NULL;
       GtkWidget *btOk   = NULL;
       GtkWidget *hbox   = NULL;
              
       //--- Criação dos widgets
       dialog = gtk_dialog_new();
       gtk_window_set_default_size(GTK_WINDOW(dialog), 220, 90);
       gtk_window_set_title(GTK_WINDOW(dialog), "Mensagem");
       
       texto  = gtk_label_new(msg);
       btOk   = gtk_button_new_with_label("OK");
       hbox   = gtk_hbutton_box_new();
       //--- Packing
       gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), texto, TRUE, TRUE, 0);
       gtk_container_add(GTK_CONTAINER(hbox), btOk);
       gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), hbox, TRUE, TRUE, 0);
       //--- Signals
       g_signal_connect_swapped(dialog, "delete_event", G_CALLBACK(gtk_widget_destroy), G_OBJECT (dialog));
       g_signal_connect_swapped(G_OBJECT(btOk), "clicked", G_CALLBACK(gtk_widget_destroy), G_OBJECT(dialog));
       
       //--- Exibe a tela de confirmacao
       gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
       gtk_widget_show_all(dialog);
       gtk_dialog_run(GTK_DIALOG(dialog));
}

//------------------------------------------------------------------------------
// Dialog perguntando se deseja realmente sair
//------------------------------------------------------------------------------
void confirma_saida(void) {
       GtkWidget *dialog = NULL;
       GtkWidget *texto  = NULL;
       GtkWidget *btYes  = NULL;
       GtkWidget *btNo   = NULL;
       GtkWidget *hbox   = NULL;
       //--- Criação dos widgets
       dialog = gtk_dialog_new();
       gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 90);
       gtk_window_set_title(GTK_WINDOW(dialog), "Sair?");
       
       texto  = gtk_label_new("Deseja realmente sair?");
       btYes  = gtk_button_new_with_label("Sim");
       btNo   = gtk_button_new_with_label("Nao");
       hbox   = gtk_hbutton_box_new();
       
       //--- Packing
       gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), texto, TRUE, TRUE, 0);
       gtk_container_add(GTK_CONTAINER(hbox), btYes);
       gtk_container_add(GTK_CONTAINER(hbox), btNo);
       gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), hbox, TRUE, TRUE, 0);
       
       //--- Signals
       g_signal_connect_swapped(dialog, "delete_event", G_CALLBACK(gtk_widget_destroy), G_OBJECT (dialog));
       g_signal_connect_swapped(G_OBJECT(btYes), "clicked", G_CALLBACK(exit), NULL);
       g_signal_connect_swapped(G_OBJECT(btNo), "clicked", G_CALLBACK(gtk_widget_destroy), G_OBJECT(dialog));
       
       //--- Exibe a tela de confirmacao
       gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
       gtk_widget_show_all(dialog);
       gtk_dialog_run(GTK_DIALOG(dialog));
}


//------------------------------------------------------------------------------
// Uma funcao para cada tipo de erro...
//------------------------------------------------------------------------------
// --- O arquivo nao é do tipo CSV
void dialog_erro_csv() {
       dialog_erro("O arquivo nao e do tipo CSV!");
}

// --- O arquivo não pode ser aberto
void dialog_erro_file() {
       dialog_erro("O arquivo nao existe ou esta protegido!");
}
// --- O registro nao existe
void dialog_erro_busca() {
       dialog_erro("O registro nao foi encontrado!");
}
// --- O campo nome esta vazio
void dialog_erro_vazio() {
       dialog_erro("O campo de nome nao pode ficar em branco!");
}
// --- A arvore foi balanceada
void dialog_msg_bal() {
       dialog_erro("A arvore binaria foi balanceada com sucesso!");
}
