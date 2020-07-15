#include <gtk/gtk.h>
#include <time.h>
#include "main.h"
//#include <signals.h>

char curr_dir[200];
char *logfile_name;
char log_path[200];

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "builder.glade", NULL);
    gtk_builder_connect_signals(builder, NULL);

    initialize_all_elements();

    getcwd(curr_dir, sizeof(curr_dir));
    sprintf(log_path,"%s/log.log",curr_dir);
    gtk_label_set_text(GTK_LABEL(logfile_path_label),log_path);

    g_timeout_add_seconds(1,(GSourceFunc) timer_handler,focus_timer_label);
    g_object_unref(builder);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
