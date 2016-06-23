#include <stdio.h>   /* sprintf */
#include <stdlib.h>  /* atoi */
#include <string.h>  /* strlen, strcmp */
#include <ctype.h>   /* isdigit */

#include "callbacks.h"

extern GtkBuilder *builder;

G_MODULE_EXPORT void on_window1_destroy(GtkObject *object, gpointer user_data){
	gtk_main_quit(); /*Stoper la boucle GTK*/
}

/* Initialisation des spinbutton */
void init_spin_button(GtkSpinButton *spb, double min_val, double max_val, double val, double step, int digits) {
	gtk_spin_button_set_digits(spb, digits);
	gtk_spin_button_set_range(spb, min_val, max_val);
	gtk_spin_button_set_value(spb, val);
	gtk_spin_button_set_increments(spb, step, step);
}

/* Initialisation des hscale */
void init_hscale(GtkHScale *hsc, double min_val, double max_val, double val, double step, int digits) {
	gtk_scale_set_digits(GTK_SCALE(hsc), digits);
	gtk_range_set_range(GTK_RANGE(hsc), min_val, max_val);
	gtk_range_set_increments(GTK_RANGE(hsc), step, step);
	gtk_range_set_value(GTK_RANGE(hsc), val);
}

/* Initialisation des hscale */
void rafraichir_affichage(){
	char msg[256];
	double val;
	GtkSpinButton *spinbutton_longueur = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spinbutton_longueur"));
	GtkLabel *label_longueur = GTK_LABEL(gtk_builder_get_object(builder, "label_longueur"));
	GtkLabel *label_message = GTK_LABEL(gtk_builder_get_object(builder, "label_message"));

	val = gtk_spin_button_get_value(spinbutton_longueur);

	sprintf_s(msg, 256, "la longueur est %.1fmm", val);
	gtk_label_set_text(label_longueur, msg);

	if (val < 5000)
		sprintf_s(msg, 256, "<b><span foreground=\"#006400\">Moins de 5000</span><b>");
	else
		sprintf_s(msg, 256, "<b><span foreground=\"#FF000\">Moins de 5000</span><b>");

	gtk_label_set_markup(label_message, msg);
}

on_button_solve_clicked(){
	int n1, n2, n3;
	char msg[128] = "";
	const char *s1, *s2;

	/* Recuperer des pointeurs vers les widgets */
	GtkLabel *section1 = GTK_LABEL(gtk_builder_get_object(builder, "section1"));
	GtkEntry *hscale_s1 = GTK_ENTRY(gtk_builder_get_object(builder, "hscale_s1"));
	GtkEntry *spinbutton_s1 = GTK_ENTRY(gtk_builder_get_object(builder, "spinbutton_s1"));
	GtkLabel *section2 = GTK_LABEL(gtk_builder_get_object(builder, "section2"));
	GtkEntry *hscale_s2 = GTK_ENTRY(gtk_builder_get_object(builder, "hscale_s2"));
	GtkEntry *spinbutton_s2 = GTK_ENTRY(gtk_builder_get_object(builder, "spinbutton_s2"));
	GtkLabel *vitesse1 = GTK_LABEL(gtk_builder_get_object(builder, "vitesse1"));
	GtkEntry *hscale_v1 = GTK_ENTRY(gtk_builder_get_object(builder, "hscale_v1"));
	GtkEntry *spinbutton_v1 = GTK_ENTRY(gtk_builder_get_object(builder, "spinbutton_v1"));
	GtkLabel *vitesse2 = GTK_LABEL(gtk_builder_get_object(builder, "vitesse2"));
	GtkEntry *hscale_v2 = GTK_ENTRY(gtk_builder_get_object(builder, "hscale_v2"));
	GtkEntry *spinbutton_v2 = GTK_ENTRY(gtk_builder_get_object(builder, "spinbutton_v2"));
	GtkLabel *pression1 = GTK_LABEL(gtk_builder_get_object(builder, "pression1"));
	GtkEntry *hscale_p1 = GTK_ENTRY(gtk_builder_get_object(builder, "hscale_p1"));
	GtkEntry *spinbutton_p1 = GTK_ENTRY(gtk_builder_get_object(builder, "spinbutton_p1"));
	GtkLabel *pression2 = GTK_LABEL(gtk_builder_get_object(builder, "pression2"));
	GtkEntry *hscale_p2 = GTK_ENTRY(gtk_builder_get_object(builder, "hscale_p2"));
	GtkEntry *spinbutton_p2 = GTK_ENTRY(gtk_builder_get_object(builder, "spinbutton_p2"));

	/* Recuperer le contenu des deux zones de saisie */
	s1 = gtk_entry_get_text(entry_nombre1);
	s2 = gtk_entry_get_text(entry_nombre2);

	/* Traitement */
	if (!strcmp(s1, "") || !strcmp(s2, "")) {
		sprintf(msg, "Champs vides");
	}
	else if (!est_nombre_entier(s1) || !est_nombre_entier(s2)) {
		sprintf(msg, "Pas des nombres");
	}
	else {
		n1 = atoi(s1);
		n2 = atoi(s2);
		n3 = n1 + n2;
		sprintf(msg, "La somme vaut %d", n3);
	}

	/* Remplacer le texte du label de message */
	gtk_label_set_text(label_message, msg);
}