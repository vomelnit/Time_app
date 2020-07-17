/// @file main.h
#include <gtk/gtk.h>

/// String of current directory of app
char curr_dir[500];
//char *logfile_name;
///String of fullpath to logfile
char log_path[500];

///Pointer to gtk builder
GtkBuilder *builder;
///Pointer to gtk main window
GtkWidget *window;
///Pointer to gtk label that displays timer
GtkWidget *focus_timer_label;
///Pointer to gtk label that displays full path to log
GtkWidget *logfile_path_label;
///String of entered symbols from gtk entry
const gchar *entered_minutes_str;
///Pointer to gtk label that displays message to enter mintes
GtkWidget *focus_info_label;
///Pointer to gtk entry in which user enter amount of minutes
GtkWidget *minutes_entry;
///Pointer to gtk start button
GtkWidget *start_btn;
///Pointer to gtk pause button
GtkWidget *pause_btn;
///Pointer to gtk stop button
GtkWidget *stop_btn;
///Pointer to gtk resume button
GtkWidget *resume_btn;
///Pointer to gtk OK button
GtkWidget *focus_ok_btn;

///Pointer to gtk dialog window for warnings
GtkWidget *dialog;
///Pointer to gtk label of dialog message
GtkWidget *dialog_msg;
///Pointer to gtk OK button in gtk dialog
GtkWidget *ok_dialog_btn;

///Show if app logging actions
GtkWidget *save_stats_checkbtn;

///Show if timer counts seconds at the moment
gboolean if_timer_on = FALSE;
///Show if app logs actions
gboolean if_logging = TRUE;
///Show if timer stared (until stop is FALSE)
gboolean if_can_change_log_status = TRUE;
///How many minutes left till timer ends
int minutes_left = 0;
///How many seconds of current minute left till timer ends
int seconds_left = 0;
///How many minutes user entered
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
