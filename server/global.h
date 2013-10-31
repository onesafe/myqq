#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <limits.h>
#include <mysql/mysql.h>

#define MAX_CLIENT 10
#define MAX_LINE 1000
#define MAX_NAME 100

char message[MAX_LINE],sys[MAX_LINE],sys_click[MAX_LINE];
char str[INET_ADDRSTRLEN];
int readcount,n;
int sockfd,new_sockfd,i,j;
int maxfd,userCount,user_link[MAX_CLIENT],userfd[MAX_CLIENT];
unsigned int cli_len;
fd_set sockset;
struct sockaddr_in client_address[MAX_CLIENT];
struct sockaddr_in server;
int listen_fd,conn_fd;
int opt=1;
pthread_t listentid,add_tid,check_tid,quit_tid;
int ret=0; 
struct check{
 char name[20];
 char pwd[20];
 char ip[25];
 char port[10];
 int fd;
};

struct check acheck[MAX_CLIENT];

struct newuser{
 char addname[20];
 char addpwd[20];
 char addip[25];
 char addport[10];
 int addfd;
 int addstatu;
};

struct newuser newuser[MAX_CLIENT];

void startserver();
void *regi_login();
void *func_quit();
void *func_check();
void *func_adduser();
void add_sockset(fd_set *sockset,int sockfd,int *user_link,int *userfd);

