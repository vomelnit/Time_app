#include <gtk/gtk.h>

char curr_dir[500];
char *logfile_name;
char log_path[500];

GtkBuilder *builder;
GtkWidget *window;
GtkWidget *focus_timer_label;
GtkWidget *logfile_path_label;
const gchar *entered_minutes_str;

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


GtkWidget *save_stats_checkbtn;


gboolean if_timer_on = FALSE;
gboolean if_logging = TRUE;
gboolean if_can_change_log_status = TRUE;
int minutes_left = 0;
int seconds_left = 0;
int minutes_entered = 0;


void on_start_btn_clicked();
void logging(char *msg);
gboolean timer_handler(GtkWidget *focus_timer_label);
void initialize_all_elements();
void on_pause_btn_clicked();
void on_resume_btn_clicked();
void on_stop_btn_clicked();
void on_focus_ok_btn_clicked();
void on_ok_dialog_btn_clicked();
void timer_stopping();
int get_minutes_from_str (const gchar *str);
void show_warning_msg(char str[]);
void on_exit_btn_clicked();
void on_main_window_destroy();
