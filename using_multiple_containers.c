#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include<gtk-2.0/gtk/gtk.h>

static void prev_tab(GtkButton *button, GtkNotebook *notebook){
    if (gtk_notebook_get_current_page(notebook) == 0)
        gtk_notebook_set_current_page(notebook, 3);
    else
        gtk_notebook_prev_page(notebook);
}

static void next_tab(GtkButton *button, GtkNotebook *notebook){
    if (gtk_notebook_get_current_page(notebook) == 3)
        gtk_notebook_set_current_page(notebook, 0);
    else
        gtk_notebook_next_page(notebook);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *notebook, *vbox, *hbox, *prev, *close;
    gint i;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 200, 300);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    notebook = gtk_notebook_new();

    prev = gtk_button_new_with_mnemonic("_Previous Tab");
    g_signal_connect(G_OBJECT(prev), "clicked",
                     G_CALLBACK(prev_tab), (gpointer)notebook);

    close = gtk_button_new_with_mnemonic("Close");
    g_signal_connect_swapped(G_OBJECT(close), "clicked",
                     G_CALLBACK(gtk_widget_destroy), (gpointer)window);

    for (i = 0; i < 4; ++i)
    {
        GtkWidget *label, *button;
        char* ret;

        /* 
         *i just know that glib provide a function called g_strdup_printf,
         *and it's a little more convinent.
         *i only need online, no need to declare, no need to free memory:
         *label = gtk_label_new(g_strdup_printf("Tab %i", i+1));
        */
        asprintf(&ret, "Tab %d", i+1);
        label = gtk_label_new(ret);
        button = gtk_button_new_with_mnemonic("_Next Tab");

        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), button, label);
        
        g_signal_connect(G_OBJECT(button), "clicked",
                         G_CALLBACK(next_tab), (gpointer)notebook);
        free(ret);
    }

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), prev, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), close, TRUE, TRUE, 0);

    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
