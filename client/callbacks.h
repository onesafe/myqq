#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define G_THREAD_FUNC(f) ((GThreadFunc)(f))

#define MAXBUF 1024
#define messcount 20

char str[INET_ADDRSTRLEN];

int sockfd,len,listfd,connfd,nready;
struct sockaddr_in dest;
struct sockaddr_in cliaddr[messcount],servaddr;
char buffer[MAXBUF+1];

fd_set allset;
struct timeval tv;
int retval,ll;
socklen_t cliaddr_len;

int listcount,readcount;
int i,j;
struct  chenge{
 int xb;
 char msg[1000];
};

struct chenge amsg;

struct close{
 GtkWidget *wcl;
 int cl;
};

struct logsi{
 char name[20];
 char pwd[20];
};
struct logsi alogsi;

struct addsi{
 char name[20];
 char pwd[20];
};
struct addsi aaddsi;
int add[messcount][2];

struct mess{
 int tu;
 char name[20];
 char ip[25];
 char port[10];
 char statu[2];
 int fd;
 GtkWidget *listup;
 GtkWidget *listdown;
 GtkTextBuffer *buffer_up;
 GtkTextIter *Iter_up;
 GtkTextBuffer *buffer_down;
 GtkTextIter *Iter_down;
 int winstu;
 int ac;

};

struct mess allmess[messcount];

struct log{
 GtkEntry *name;
 GtkEntry *pwd;
};
struct log login;

struct widadd{
 GtkEntry *name;
 GtkEntry *pwd;
};
struct widadd wadd;

enum {
 PIXBUF_COL,
 TEXT_COL
};
char sysmsg[1000];

void combochange_log(int ,char *);
void func_action(int);
void dialog_sysmsg(GtkWidget *widget,gpointer *data);
void destroy_sysmsg(GtkWidget *widget,gpointer *data);
void on_delete_event(GtkWidget *widget,gpointer data);
void delete_event(GtkWidget *widget,GdkEvent *event,gpointer data);
void wri_to(GtkWidget *widget,gpointer data);
void func_dialog(void);

gboolean selection_changed(GtkWidget *widget,gpointer data);

GtkWidget *treeview_frend_list;
GtkTreeStore *store1;

GtkWidget *window_login;
GtkWidget *window_adduser;
GtkWidget *create_login(void);
GtkWidget *create_adduser(void);
GtkTreeModel *createModel();
GtkWidget *create_list(void);
GtkWidget *create_toto(int);
//GtkWidget *create_sysmsg(void);
GtkWidget *create_ipport(void);
void func_button_login(GtkWidget *widget,gpointer data);
void func_button_adduser(GtkWidget *widget,gpointer data);
void func_button_update(GtkWidget *widget,gpointer data);
void go_to();
void create_log(void);
void fanhui_log(void);
void add_sockset(fd_set *sockset,int sockfd,int user_link,int add[messcount][2]);

