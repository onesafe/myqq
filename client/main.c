#include "callbacks.h"

int main(int argc,char *argv[])
{
 if(!g_thread_supported())
     g_thread_init(NULL);
 gdk_threads_init();

 gtk_init(&argc,&argv);
 window_login=create_login();
 gtk_widget_show_all(window_login);

 gdk_threads_enter();
 gtk_main();
 gdk_threads_leave();

 return FALSE;
}
