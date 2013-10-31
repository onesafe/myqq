#include "global.h"
#include <mysql/mysql.h>

int main(int argc,char *argv[])
{
    startserver();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
void startserver()
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {   printf("create socket failed \n");  }

    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(8000);

    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if(bind(sockfd,(struct sockaddr *)&server,sizeof(server))==-1)
    {  printf("bind failed\n");  }
    listen(sockfd,10);
    cli_len=sizeof(client_address);
    printf("服务器成功启动！.\n");
    for(i=0;i<MAX_CLIENT;i++)
        user_link[i]=0;
    userCount=0;
    FD_ZERO(&sockset);
    FD_SET(sockfd,&sockset);
    maxfd=max(maxfd,sockfd+1);

    ret=pthread_create(&listentid,NULL,regi_login,NULL);
    if(ret!=0)
    {
        printf("create listen_pthread failed\n");
    }
    pthread_join(listentid,NULL);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++

void *regi_login()
{
    printf("already regi_login.\n");
    for(;;)
    {
        n=select(maxfd,&sockset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&sockset)&&(userCount=user_free(user_link))>=0)
        {
            new_sockfd=accept(sockfd,(struct sockaddr *)&client_address[userCount],&cli_len);
            if(new_sockfd<0)
            {
                user_link[userCount]=0;
            }else{
                printf("已有新连接!\n");
                printf("userCount=%d\n",userCount);
                printf("new_sockfd=%d\n",new_sockfd);
                user_link[userCount]=1;
                userfd[userCount]=new_sockfd;
                FD_SET(new_sockfd,&sockset);
                maxfd=max(maxfd,new_sockfd+1);
                printf("userfd[userCount]=%d\n",userfd[userCount]);
                printf("maxfd=%d\n",maxfd);
            }
            add_sockset(&sockset,sockfd,user_link,userfd);
            continue;  
        }
        for(i=0;i<MAX_CLIENT;i++)
        {
            if((user_link[i]==1)&&(FD_ISSET(userfd[i],&sockset)))
            {
                printf("读前\n");
                readcount=read(userfd[i],message,MAX_LINE);
                printf("读后readcount=%d\n",readcount);
                if(readcount==0)
                {
                    printf("客户%d 关闭\n",userfd[i]);
                    user_link[i]=0;
                    FD_CLR(userfd[i],&sockset);
                    char ipip[100];
                    char por[10];
                    char fd[5];
                    memset(ipip,0,100);
                    sprintf(ipip,"%s",inet_ntop(AF_INET,&client_address[i].sin_addr,str,sizeof(str)));
                    strcat(ipip,":");
                    sprintf(por,"%d",ntohs(client_address[i].sin_port));
                    strcat(ipip,por);
                    strcat(ipip,":");
                    sprintf(fd,"%d",userfd[i]);
                    strcat(ipip,fd);
                    printf("ipip=%s\n",ipip);
                    ret=pthread_create(&quit_tid,NULL,func_quit,&ipip);
                    if(ret==-1)
                    {
                        printf("create quit thread error\n");
                    }
                    bzero((char *)&client_address[i],sizeof(client_address[i]));
                }else if(readcount>0){
                    char *token;
                    message[readcount]='\0';
                    token=strtok(message,":");

                    if(strcmp(token,"useradd")==0)
                    {
                        printf("进入useradd:\n");
                        token=strtok(NULL,":");
                        printf("token=%s\n",token);
                        strcpy(newuser[i].addname,token);
                        printf("newuser[i].name=%s\n",newuser[i].addname);

                        token=strtok(NULL,":");
                        strcpy(newuser[i].addpwd,token);
                        printf("token=%s\n",token);
                        printf("newuser[i].pwd=%s\n",newuser[i].addpwd);

                        sprintf(newuser[i].addip,"%s",inet_ntop(AF_INET,&client_address[i].sin_addr,str,sizeof(str)));
                        printf("token=%s\n",newuser[i].addip);

                        sprintf(newuser[i].addport,"%d",ntohs(client_address[i].sin_port));
                        printf("token=%s\n",newuser[i].addport);

                        newuser[i].addfd=userfd[i];
                        newuser[i].addstatu=0;
                        printf("useradd:\n");
                        ret=pthread_create(&add_tid,NULL,func_adduser,&newuser[i]);
                        if(ret==-1)
                        {printf("create add_thread failed\n");}
                    }
                    if(strcmp(token,"usercheck")==0)
                    {
                        token=strtok(NULL,":");
                        strcpy(acheck[i].name,token);
                        token=strtok(NULL,":");
                        strcpy(acheck[i].pwd,token);
                        sprintf(acheck[i].ip,"%s",inet_ntop(AF_INET,&client_address[i].sin_addr,str,sizeof(str)));
                        sprintf(acheck[i].port,"%d",ntohs(client_address[i].sin_port));

                        acheck[i].fd=userfd[i];
                        ret=pthread_create(&check_tid,NULL,func_check,&acheck[i]);
                        if(ret==-1)
                        {printf("create check_thread failed\n");}
                    }
                    if(strcmp(token,"accet")==0)
                    {
                        printf("%s\n",token);
                        write(userfd[i],token,strlen(token));
                    }
                }

            }
        }
        add_sockset(&sockset,sockfd,user_link,userfd);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void *func_adduser(struct newuser *k)
{
    char sql[300];
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql_init(&conn);
    if(!mysql_real_connect(&conn,"127.0.0.1","root","123456","myqq",0,NULL,0))
    {
        char failed[15];
        strcpy(failed,"sqlfailed");
        write(k->addfd,failed,strlen(failed));
    }else{
        sprintf(sql,"insert into usermsg(username,userpwd,userip,userport,userstatu) values('%s','%s','%s','%s','%d')",k->addname,k->addpwd,k->addip,k->addport,k->addstatu);
        printf("sql=%s\n",sql);

        mysql_query(&conn,sql);
        unsigned int mysql_ac;
        mysql_ac=mysql_affected_rows(&conn);
        printf("mysql_ac=%u\n",mysql_ac);
        if(mysql_ac==1)
        {
            char ut[10];
            sprintf(ut,"on:%s",k->addname);
            write(k->addfd,ut,strlen(ut));
            printf("%s 已注册\n",k->addname);

            //++++++向客户端发送注册用户的信息++++++++++++
            char sigink[100];
            memset(sigink,'\0',100);
            sprintf(sigink,"sigin:%s:%s:%s:%d",k->addname,k->addip,k->addport,k->addstatu);
            for(j=0;j<MAX_CLIENT;j++)
            {
                if((user_link[j]==1)&&(userfd[j]!=k->addfd))
                { write(userfd[j],sigink,strlen(sigink)); }
            }

        }else{
            char ut[5]="off";
            write(k->addfd,ut,strlen(ut));
        }
        mysql_close(&conn);
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void *func_check(struct check *k)
{
    char sql[300];
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql_init(&conn);
    if(!mysql_real_connect(&conn,"127.0.0.1","root","123456","myqq",0,NULL,0))

    {
        char failed[15];
        strcpy(failed,"sqlfailed");
        write(k->fd,failed,strlen(failed));
    }else {
        sprintf(sql,"select username,userpwd,userstatu from usermsg where username='%s' and userpwd='%s'",k->name,k->pwd);
        printf("sql=%s\n",sql);
        mysql_query(&conn,sql);
        if((result=mysql_store_result(&conn))==NULL)
        { fprintf(stderr,"Fail to get the result.\n"); }
        row=mysql_fetch_row(result);
        if(row!=0)
        {
            printf("row[0]=%s,row[1]=%s,row[2]=%s\n",row[0],row[1],row[2]);
            if(!strcmp(row[0],k->name)&&!strcmp(row[1],k->pwd)&&!atoi(row[2]))
            {
                memset(sql,0,200);
                sprintf(sql,"select userip,userport from usermsg where username='%s' and userpwd='%s'",k->name,k->pwd); 
                mysql_query(&conn,sql);
                result=mysql_store_result(&conn);
                row=mysql_fetch_row(result);
                printf("%s\n",sql);
                if((strcmp(row[0],k->ip)!=0)||(strcmp(row[1],k->port)!=0))
                {
                    memset(sql,'\0',300);
                    sprintf(sql,"update usermsg set  userip='%s',userport='%s',userstatu=1 where username='%s' and userpwd='%s'",k->ip,k->port,k->name,k->pwd);
                    printf("%s\n",sql);
                    if(mysql_query(&conn,sql))
                    {printf("update usermsg error\n"); }
                    else
                        printf("update success\n");
                    char delu[100];
                    memset(delu,'\0',100);
                    sprintf(delu,"delu:%s:%s:%s",k->name,k->ip,k->port);
                    for(j=0;j<MAX_CLIENT;j++)
                    {
                        if((user_link[j]==1)&&(userfd[j]!=k->fd))
                        { write(userfd[j],delu,strlen(delu)); }
                    }
                }else{
                    memset(sql,'\0',300);
                    sprintf(sql,"update usermsg set userstatu=1 where username=%s and userpwd='%s'",k->name,k->pwd);

                    printf("%s\n",sql);
                    mysql_query(&conn,sql);
                    char delu[100];
                    memset(delu,'\0',100);
                    sprintf(delu,"delu:%s:%s:%s",k->name,k->ip,k->port);
                    for(j=0;j<MAX_CLIENT;j++)
                    {
                        if((user_link[j]==1)&&(userfd[j]!=k->fd))
                        { write(userfd[j],delu,strlen(delu)); }
                    }
                } 
                char name[40];
                strcpy(name,k->name);
                strcat(name," 已登录");
                printf("--%s--\n",name);

                mysql_free_result(result);
                sprintf(sql,"select count(*) as title from usermsg");
                mysql_query(&conn,sql);
                result=mysql_store_result(&conn);
                row=mysql_fetch_row(result);
                printf("title=%s\n",row[0]);
                char ucount[15];
                sprintf(ucount,"ucount:%s:",row[0]);
                write(k->fd,ucount,strlen(ucount));
                usleep(150000);
                mysql_free_result(result);

                memset(sql,0,300);
                sprintf(sql,"select username,userip,userport,userstatu from usermsg where username='%s' and userpwd='%s'",k->name,k->pwd);
                printf("%s\n",sql);
                mysql_query(&conn,sql);
                result=mysql_store_result(&conn);
                row=mysql_fetch_row(result);
	        int i;
		char aaaa[200];
		memset(aaaa, 0, 200);
		strcpy(aaaa, "sigin");
		for (i = 0; i < 4; i++) {
	        	strcat(aaaa, ":");
			strcat(aaaa, row[i]);
	    	}
	    	write(k->fd, aaaa, strlen(aaaa));
	    	usleep(150000);;
                mysql_free_result(result);
	        memset(sql, 0, 300);
		sprintf(sql, "select username,userip,userport,userstatu from usermsg where username != '%s'", k->name);
                mysql_query(&conn,sql);
                result=mysql_store_result(&conn);
                while((row=mysql_fetch_row(result))!=NULL)
                {
                    int i;
                    char sigin[200];
                    memset(sigin,0,200);
                    strcpy(sigin,"sigin");
                    for(i=0;i<4;i++)
                    {
                printf("1----\n");
                        strcat(sigin,":");
                        strcat(sigin,row[i]);
                    }
                    sigin[strlen(sigin)]='\0';
                    write(k->fd,sigin,strlen(sigin));
                    usleep(150000);
                }
                usleep(150000);
                char over[7]="over";
                write(k->fd,over,strlen(over));
                mysql_free_result(result);
                printf("on\n");

            }else{
                printf("ut=\n");
                char ut[10]="chkoff";
                printf("ut=%s\n",ut);
                write(k->fd,ut,strlen(ut));
            }
        }
        printf("ut111=\n");
        mysql_close(&conn);
    }
    printf("check_name: %s\n",k->name);
    printf("check_pwd: %s\n",k->pwd);
    printf("check_fd: %d\n",k->fd);

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void add_sockset(fd_set *sockset,int sockfd,int *user_link,int *userfd)
{
    int i;
    FD_ZERO(sockset);
    FD_SET(sockfd,sockset);
    for(i=0;i<MAX_CLIENT;i++)
    {
        if(user_link[i]==1)
        { FD_SET(userfd[i],sockset); }
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int user_free(int user_link[MAX_CLIENT])
{
    int i=0;
    while((user_link[i]!=0)&&(i<MAX_CLIENT))
        i++;
    if(i==MAX_CLIENT)
        return -1;
    return (i);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int max(int a,int b)
{
    return a>b?a:b;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void *func_quit(char ipip[40])
{
    char ip[25];
    char port[10];
    int fd;
    char *token;
    token=strtok(ipip,":");
    strcpy(ip,token);
    token=strtok(NULL,":");
    strcpy(port,token);
    token=strtok(NULL,":");
    fd=atoi(token);

    char quit[40];
    strcpy(quit,"quit");
    strcat(quit,":");
    strcat(quit,ip);
    strcat(quit,":");
    strcat(quit,port);
    printf("quit=%s\n",quit);

    printf("fd=%d\n",fd);

    char sql[300];
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql_init(&conn);
    if(!mysql_real_connect(&conn,"127.0.0.1","root","123456","myqq",0,NULL,0))
    {
        char failed[15]="sqlfailed";
        write(fd,failed,strlen(failed));
    }else{
        sprintf(sql,"update usermsg set userstatu=0 where userip='%s' and userport='%s'",ip,port);
        mysql_query(&conn,sql);
        for(j=0;j<MAX_CLIENT;j++)
        {
            if((user_link[j]==1)&&(userfd[j]!=fd))
            { write(userfd[j],quit,strlen(quit)); }
        }

        memset(sql,0,300);
        sprintf(sql,"select username from usermsg where userip='%s' and userport='%s'",ip,port);
        mysql_query(&conn,sql);
        result=mysql_store_result(&conn);
        row=mysql_fetch_row(result);
        if(row!=0)
        {
            char name[20];
            strcpy(name,row[0]);
            printf("%s 已退出\n",name);
        }
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
