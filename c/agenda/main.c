//------------------------------------------------------------------------------
// MAIN.C
// Arquivo principal.
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

//------------------------------------------------------------------------------
// FUNCAO PRINCIPAL
//------------------------------------------------------------------------------
int main (int argc, char *argv[]) {
       // Inicializa o GTK
       g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
       gtk_init (&argc, &argv);
       g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

       // Chama a função para montar a interface
       create_interface();
       
       gtk_main ();
       
       return 0;
}
