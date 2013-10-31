#include "callbacks.h"

int main(int argc, char **argv)
{
	GtkWidget *window_server;

	if (!g_thread_supported())
		g_thread_init(NULL);
	gdk_threads_init();

	gtk_init(&argc, &argv);
	window_server = create_window();
	gtk_widget_show_all(window_server);

	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();

	return FALSE;
}
