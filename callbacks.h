#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

G_MODULE_EXPORT void on_window1_destroy(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button_addition_clicked(GtkObject *object, gpointer user_data);

#endif /* CALLBACKS_H */
