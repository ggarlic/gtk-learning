/* exercise 2-2 */
#include<gtk-2.0/gtk/gtk.h>

#define FIRST_NAME "Bo"
#define LAST_NAME "Yang"

static void destroy (GtkWidget *window, gpointer data) {
    gtk_main_quit ();
}

static gboolean delete_event (GtkWidget *window, GdkEvent *event,
        gpointer data) {
    return FALSE;
}
static gboolean key_press_event (GtkWidget *window, GdkEvent *event,
        GtkLabel *label) {

    /*
     * check this url for a mistake i made:
     * https://mail.gnome.org/archives/gtk-list/2009-December/msg00154.html
     */
    const gchar *in_label = gtk_label_get_text(GTK_LABEL(label));
    gchar *in_title = g_strdup(gtk_window_get_title(GTK_WINDOW(window)));

    gtk_window_set_title(GTK_WINDOW(window), in_label);
    gtk_label_set_text(GTK_LABEL(label), in_title);

    g_free(in_title);

    return FALSE;
}

static void title_changed (GtkWidget *window, GdkEvent *event, gpointer data){
    gchar *text;
    g_object_get(window, "title", &text, NULL);
    g_message("new title is \"%s\"", text);
}


int main (int argc, char *argv[]) {
    GtkWidget *window, *label;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_object_set(window, "title", FIRST_NAME, "width-request", 200,
            "height-request", 300, "border-width", 10, "resizable", TRUE,
            NULL);

    label = gtk_label_new (LAST_NAME);
    g_object_set(label, "selectable", TRUE, NULL);

    g_signal_connect(G_OBJECT (window), "destroy",
            G_CALLBACK(destroy), NULL);
    g_signal_connect(G_OBJECT (window), "delete_event",
            G_CALLBACK(delete_event), NULL);
    g_signal_connect(G_OBJECT(window), "key-press-event",
            G_CALLBACK(key_press_event), label);
    g_signal_connect(G_OBJECT(window), "notify::title",
            G_CALLBACK(title_changed), NULL);

    gtk_container_add (GTK_CONTAINER (window), label);
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}

