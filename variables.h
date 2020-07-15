#include <gtk/gtk.h>

const gchar *entered_minutes_str;

GtkBuilder *builder;
GtkWidget *window;

GtkWidget *focus_info_label;
GtkWidget *focus_timer_label;
GtkWidget *minutes_entry;

GtkWidget *start_btn;
GtkWidget *pause_btn;
GtkWidget *stop_btn;
GtkWidget *resume_btn;
GtkWidget *focus_ok_btn;

GtkWidget *dialog;
GtkWidget *dialog_msg;
GtkWidget *ok_dialog_btn;

GtkWidget *logfile_path_label;
GtkWidget *save_stats_checkbtn;


gboolean if_timer_on = FALSE;
gboolean if_logging = TRUE;
gboolean if_can_change_log_status = TRUE;
int minutes_left = 0;
int seconds_left = 0;
int minutes_entered = 0;
