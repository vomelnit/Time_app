#include <time.h>
#include "main.h"




int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "xml/builder.glade", NULL);
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

void on_start_btn_clicked(){
  int entered_number = get_minutes_from_str(gtk_entry_get_text(GTK_ENTRY (minutes_entry)));
  if (entered_number!=-1){
    minutes_entered = entered_number;
    minutes_left = minutes_entered;
    seconds_left = 0;
    gtk_widget_set_visible (minutes_entry,FALSE);
    gtk_widget_set_visible (focus_info_label,FALSE);
    gtk_widget_set_visible (focus_timer_label,TRUE);
    gtk_widget_set_visible (start_btn,FALSE);
    gtk_widget_set_visible (pause_btn,TRUE);
    gtk_widget_set_visible (stop_btn,TRUE);
    if_timer_on = TRUE;
    if_can_change_log_status = FALSE;
    logging("Start");
  }
  gtk_entry_set_text(GTK_ENTRY (minutes_entry),"");
}

void logging(char *msg){
  FILE *log;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  log = fopen("log.log", "a+");
  if (log == NULL) show_warning_msg("Problem with logging");
  else {
    fprintf(log,"%d-%02d-%02d %02d:%02d:%02d %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, msg);
    fclose(log);
  }
}

gboolean timer_handler(GtkWidget *focus_timer_label)
{
    if (if_timer_on){
      char time_left_str[7];
      if ((seconds_left == 0)&&(minutes_left == 0)){
          timer_stopping();
          return TRUE;
      }
      else if ((seconds_left == 0)&&(minutes_left!=0)){
        minutes_left--;
        seconds_left = 59;
      }
      else seconds_left--;
      sprintf(time_left_str,"%d:%02d",minutes_left, seconds_left);
      gtk_label_set_text(GTK_LABEL(focus_timer_label),time_left_str);
  }
    return TRUE;
}

void initialize_all_elements(){
  window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  dialog = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_gtk"));
  dialog_msg = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_msg"));
  ok_dialog_btn = GTK_WIDGET(gtk_builder_get_object(builder, "ok_dialog_btn"));
  focus_info_label = GTK_WIDGET(gtk_builder_get_object(builder, "focus_info_label"));
  focus_timer_label = GTK_WIDGET(gtk_builder_get_object(builder, "focus_timer_label"));
  minutes_entry = GTK_WIDGET(gtk_builder_get_object(builder, "minutes_entry"));

  start_btn = GTK_WIDGET(gtk_builder_get_object(builder, "start_btn"));
  pause_btn = GTK_WIDGET(gtk_builder_get_object(builder, "pause_btn"));
  stop_btn = GTK_WIDGET(gtk_builder_get_object(builder, "stop_btn"));
  resume_btn = GTK_WIDGET(gtk_builder_get_object(builder, "resume_btn"));
  focus_ok_btn = GTK_WIDGET(gtk_builder_get_object(builder, "focus_ok_btn"));

  logfile_path_label = GTK_WIDGET(gtk_builder_get_object(builder, "logfile_path_label"));
  save_stats_checkbtn = GTK_WIDGET(gtk_builder_get_object(builder, "save_stats_checkbtn"));
}

void on_pause_btn_clicked(){
  gtk_widget_set_visible (pause_btn,FALSE);
  gtk_widget_set_visible (resume_btn,TRUE);
  if_timer_on = FALSE;
  logging("Pause");
}

void on_resume_btn_clicked(){
  gtk_widget_set_visible (pause_btn,TRUE);
  gtk_widget_set_visible (resume_btn,FALSE);
  if_timer_on = TRUE;
  logging("Unpause");
}

void on_stop_btn_clicked(){
  gtk_widget_set_visible (pause_btn,FALSE);
  gtk_widget_set_visible (resume_btn,FALSE);
  gtk_widget_set_visible (stop_btn,FALSE);
  gtk_widget_set_visible (minutes_entry,FALSE);
  gtk_widget_set_visible (focus_info_label,FALSE);
  gtk_widget_set_visible (focus_timer_label,FALSE);
  gtk_widget_set_visible (start_btn,TRUE);
  timer_stopping();
  if_can_change_log_status = TRUE;
}

void on_focus_ok_btn_clicked(){
  gtk_widget_set_visible (pause_btn,FALSE);
  gtk_widget_set_visible (resume_btn,FALSE);
  gtk_widget_set_visible (stop_btn,FALSE);
  gtk_widget_set_visible (minutes_entry,TRUE);
  gtk_widget_set_visible (focus_info_label,TRUE);
  gtk_widget_set_visible (focus_timer_label,FALSE);
  gtk_widget_set_visible (start_btn,TRUE);
  gtk_label_set_text(GTK_LABEL(focus_timer_label),"");
}

void on_ok_dialog_btn_clicked(){
  gtk_widget_hide (dialog);
  gtk_label_set_text(GTK_LABEL(dialog_msg),"");
}


void timer_stopping(){
  char focus_conclusion[50];
  sprintf(focus_conclusion,"Focusing time: %d minutes",minutes_entered-minutes_left);
  gtk_label_set_text(GTK_LABEL(focus_timer_label),focus_conclusion);
  gtk_widget_set_visible (focus_info_label,FALSE);
  gtk_widget_set_visible (focus_ok_btn,TRUE);
  gtk_widget_set_visible (focus_timer_label,TRUE);
  gtk_widget_set_visible (start_btn,FALSE);
  gtk_widget_set_visible (pause_btn,FALSE);
  gtk_widget_set_visible (stop_btn,FALSE);
  if_timer_on = FALSE;
  minutes_entered = 0;
  minutes_left = 0;
  seconds_left = 0;
  logging("Stop");
}

int get_minutes_from_str (const gchar *str){
  int min_of_focus = 0;
  if (strlen(str)>3) {
    show_warning_msg("Too many symbols");
    return -1;
  }
  else if (strlen(str)<1) {
    show_warning_msg("Enter minutes");
    return -1;
  }
  for (int i = 0; i<strlen(str);i++){
    if ((str[i]<'0')||(str[i]>'9')){
      show_warning_msg("Only digits");
      return -1;
    }
    else min_of_focus = min_of_focus*10 + str[i]-'0';
  }
  if ((min_of_focus<5)||(min_of_focus>180)) {
    show_warning_msg("Enter value between 5 and 180");
    return -1;
  }
  return min_of_focus;
}

void show_warning_msg(char str[]){
  g_print("%s",str);
  gtk_label_set_text(GTK_LABEL(dialog_msg),str);
  gtk_widget_show(dialog);
}

void on_exit_btn_clicked(){
    if (if_can_change_log_status == FALSE) logging("Stop");
    gtk_main_quit();
}

void on_main_window_destroy()
{
  if (if_can_change_log_status == FALSE) logging("Stop");
    gtk_main_quit();
}
