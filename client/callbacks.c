#include "callbacks.h"


int wrilog=0,wriadd=0,jinji=0;
int fdstatu=1,dia=0;
int add_stut=0,log_stut=0;
int serverport;
char serverip[30];
char ch_dialog[100];
int opt=1,maxfd=-1,k=0,top=1;
int xx=0;
GtkWidget *window1;

//创建一个ico图标
GdkPixbuf *create_pixbuf(const gchar *filename)
{
    GdkPixbuf *pixbuf;
    GError *error=NULL;
    pixbuf=gdk_pixbuf_new_from_file(filename,&error);
    if(!pixbuf)
    {
        fprintf(stderr,"%s\n",error->message);
        g_error_free(error);
    }
    return pixbuf;
}

//启动窗口+++++++++++++++++++++++++++++++++++++
GtkWidget *create_login(void)
{
    GtkWidget *window_login;
    GtkWidget *vbox1;
    GtkWidget *label_welcome;
    GtkWidget *label_user;
    GtkWidget *label_pwd;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *label6;
    GtkWidget *entry_user;
    GtkWidget *entry_pwd;
    GtkWidget *button_login;
    GtkWidget *button_adduser;
    GtkWidget *hbox1;
    GtkWidget *hbox2;
    GtkWidget *hbox3;

    //窗体初始化
    window_login=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_login,400,260);
    gtk_window_set_icon(GTK_WINDOW(window_login),create_pixbuf("3.png"));
    gtk_window_set_title(GTK_WINDOW(window_login),"Login screen");
    gtk_window_set_resizable(GTK_WINDOW(window_login),FALSE);
    gtk_window_set_position(GTK_WINDOW(window_login),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window_login),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

    //设置vbox容器
    vbox1=gtk_vbox_new(FALSE,0);
    gtk_widget_show(vbox1);
    gtk_container_add(GTK_CONTAINER(window_login),vbox1);

    label_welcome=gtk_label_new("Welcome to use");
    gtk_widget_show(label_welcome);
    gtk_box_pack_start(GTK_BOX(vbox1),label_welcome,FALSE,FALSE,0);
    gtk_widget_set_size_request(label_welcome,-1,68);

    //+++++第一行++++++++++++++++++++++++++++++++++++
    hbox1=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox1);
    gtk_box_pack_start(GTK_BOX(vbox1),hbox1,TRUE,TRUE,0);

    label_user=gtk_label_new("Username :");
    gtk_widget_show(label_user);
    gtk_box_pack_start(GTK_BOX(hbox1),label_user,FALSE,FALSE,0);
    gtk_widget_set_size_request(label_user,110,-1);
    gtk_label_set_justify(GTK_LABEL(label_user),GTK_JUSTIFY_RIGHT);
    gtk_misc_set_alignment(GTK_MISC(label_user),1,0.52);

    entry_user=gtk_entry_new();
    gtk_widget_show(entry_user);
    gtk_box_pack_start(GTK_BOX(hbox1),entry_user,TRUE,TRUE,0);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry_user),8226);

    label1=gtk_label_new("");
    gtk_widget_show(label1);
    gtk_box_pack_start(GTK_BOX(hbox1),label1,FALSE,FALSE,0);
    gtk_widget_set_size_request(label1,90,-1);

    //++++++++++第二行+++++++++++++++++++++++++++++++++++++++++
    hbox2=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox2);
    gtk_box_pack_start(GTK_BOX(vbox1),hbox2,TRUE,TRUE,0);

    label_pwd=gtk_label_new("Password :");
    gtk_widget_show(label_pwd);
    gtk_box_pack_start(GTK_BOX(hbox2),label_pwd,FALSE,FALSE,0);
    gtk_widget_set_size_request(label_pwd,110,-1);
    gtk_label_set_justify(GTK_LABEL(label_pwd),GTK_JUSTIFY_RIGHT);
    gtk_misc_set_alignment(GTK_MISC(label_pwd),1,0.52);

    entry_pwd=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pwd),FALSE);
    gtk_widget_show(entry_pwd);
    gtk_box_pack_start(GTK_BOX(hbox2),entry_pwd,TRUE,TRUE,0);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry_pwd),8226);

    label2=gtk_label_new("");
    gtk_widget_show(label2);
    gtk_box_pack_start(GTK_BOX(hbox2),label2,FALSE,FALSE,0);
    gtk_widget_set_size_request(label2,90,-1);

    //++++++++++++第三行+++++++++++++++++++++++++++++++++++++++++++

    hbox3=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox3);
    gtk_box_pack_start(GTK_BOX(vbox1),hbox3,TRUE,TRUE,0);
    gtk_widget_set_size_request(hbox3,-1,3);

    label3=gtk_label_new("");
    gtk_widget_show(label3);
    gtk_box_pack_start(GTK_BOX(hbox3),label3,FALSE,FALSE,0);
    gtk_widget_set_size_request(label3,115,-1);

    button_login=gtk_button_new_with_mnemonic("Login");
    gtk_widget_show(button_login);
    gtk_box_pack_start(GTK_BOX(hbox3),button_login,FALSE,FALSE,0);
    gtk_widget_set_size_request(button_login,60,-1);

    label4=gtk_label_new("");
    gtk_widget_show(label4);
    gtk_box_pack_start(GTK_BOX(hbox3),label4,FALSE,FALSE,0);
    gtk_widget_set_size_request(label4,53,-1);

    button_adduser=gtk_button_new_with_mnemonic("Register");
    gtk_widget_show(button_adduser);
    gtk_box_pack_start(GTK_BOX(hbox3),button_adduser,FALSE,FALSE,0);
    gtk_widget_set_size_request(button_adduser,60,-1);

    label5=gtk_label_new("");
    gtk_widget_show(label5);
    gtk_box_pack_start(GTK_BOX(hbox3),label5,FALSE,FALSE,0);

    //放一个label在最后一行+++++++++++++++++++++++++++++++++++ 
    label6=gtk_label_new("");
    gtk_widget_show(label6);
    gtk_box_pack_start(GTK_BOX(vbox1),label6,FALSE,FALSE,0);
    gtk_widget_set_size_request(label6,-1,43);
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    login.name=GTK_ENTRY(entry_user);
    login.pwd=GTK_ENTRY(entry_pwd);

    g_signal_connect(G_OBJECT(button_login),"clicked",G_CALLBACK(func_button_login),(gpointer)&login);
    g_signal_connect(G_OBJECT(button_adduser),"clicked",G_CALLBACK(func_button_adduser),NULL);

    return window_login;
}

//++++++++++++注册按钮调用函数++++++++++++++++++++++++++
void func_button_adduser(GtkWidget *widget,gpointer data)
{
    gtk_widget_hide(window_login);
    window_adduser=create_adduser();
    gtk_widget_show_all(window_adduser); 
}

//++++++++++登录按钮调用函数+++++++++++++++++++++++++++++++++++

void func_button_login(GtkWidget *widget,gpointer data)
{
    struct log *aa = (struct log *)data;
    gchar *name = (gchar *) gtk_entry_get_text(GTK_ENTRY(aa->name));
    gchar *pwd = (gchar *) gtk_entry_get_text(GTK_ENTRY(aa->pwd));
    memset(alogsi.name,'\0',strlen(alogsi.name));
    memset(alogsi.pwd,'\0',strlen(alogsi.pwd));
    strcpy(alogsi.name,name);
    strcpy(alogsi.pwd, pwd);
    if (fdstatu) {
        g_thread_create(G_THREAD_FUNC(go_to), NULL, FALSE, NULL);
        fdstatu = 0;
    }
    printf("start create list\n");
    wrilog = 1;
    create_log();
} 

//++++++++++创建登陆，放入线程，根据条件创建+++++++
void create_log(void)
{
    while (1) {
        if (log_stut == 1) {
            GtkWidget *window_list;
            window_list = create_list();
            gtk_widget_show_all(window_list);
            printf("kkkkkkkkkkkk\n");
            break;
        }
    }
    gtk_widget_hide(window_login);
}
//++++++++++注册用户窗口++++++++++++++++++++++++++++++++++++++++
GtkWidget *create_adduser(void)
{
    GtkWidget *window_adduser;
    GtkWidget *vbox2;
    GtkWidget *label7;
    GtkWidget *label8;
    GtkWidget *label9;
    GtkWidget *label10;
    GtkWidget *label_user;
    GtkWidget *label_pwd1;
    GtkWidget *label_warn;
    GtkWidget *entry_user1;
    GtkWidget *entry_pwd1;
    GtkWidget *button_submit;
    GtkWidget *hbox4;
    GtkWidget *hbox5;
    GtkWidget *hbox6;

    window_adduser=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_adduser,300,250);
    gtk_window_set_title(GTK_WINDOW(window_adduser),"register info"); 
    gtk_window_set_icon_name(GTK_WINDOW(window_adduser),"stock_smiley-18");
    gtk_window_set_resizable(GTK_WINDOW(window_adduser),FALSE);
    gtk_window_set_position(GTK_WINDOW(window_adduser),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window_adduser),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

    vbox2=gtk_vbox_new(FALSE,0);
    gtk_widget_show(vbox2);
    gtk_container_add(GTK_CONTAINER(window_adduser),vbox2);

    label7=gtk_label_new("welcome register our software");
    gtk_widget_show(label7);
    gtk_box_pack_start(GTK_BOX(vbox2),label7,FALSE,FALSE,0);
    gtk_widget_set_size_request(label7,-1,50);

    //++++++++++++++++++++++++++++++++++++++++++++

    hbox4=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox4);
    gtk_box_pack_start(GTK_BOX(vbox2),hbox4,TRUE,TRUE,0); 

    label_user=gtk_label_new("Username :");
    gtk_widget_show(label_user);
    gtk_box_pack_start(GTK_BOX(hbox4),label_user,FALSE,FALSE,0);
    gtk_label_set_justify(GTK_LABEL(label_user),GTK_JUSTIFY_RIGHT);
    gtk_widget_set_size_request(label_user,70,-1);
    gtk_misc_set_alignment(GTK_MISC(label_user),1,0.5);

    entry_user1=gtk_entry_new();
    gtk_widget_show(entry_user1);
    gtk_box_pack_start(GTK_BOX(hbox4),entry_user1,TRUE,TRUE,0);
    gtk_widget_set_size_request(entry_user1,100,-1);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry_user1),8226);

    label8=gtk_label_new("*");
    gtk_widget_show(label8);
    gtk_box_pack_start(GTK_BOX(hbox4),label8,FALSE,FALSE,0);
    gtk_widget_set_size_request(label8,70,-1);

    //+++++++++++++++++++++++++++++++++++++++++++++++++

    hbox5=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox5);
    gtk_box_pack_start(GTK_BOX(vbox2),hbox5,FALSE,FALSE,0);

    label_pwd1=gtk_label_new("Password :");
    gtk_widget_show(label_pwd1);
    gtk_box_pack_start(GTK_BOX(hbox5),label_pwd1,FALSE,FALSE,0);
    gtk_widget_set_size_request(label_pwd1,70,51);
    gtk_misc_set_alignment(GTK_MISC(label_pwd1),1,0.5);

    entry_pwd1=gtk_entry_new();
    gtk_widget_show(entry_pwd1);
    gtk_box_pack_start(GTK_BOX(hbox5),entry_pwd1,TRUE,TRUE,0);
    gtk_widget_set_size_request(entry_pwd1,-1,29);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry_pwd1),8226);

    label9=gtk_label_new("*");
    gtk_widget_show(label9);
    gtk_box_pack_start(GTK_BOX(hbox5),label9,FALSE,FALSE,0);
    gtk_widget_set_size_request(label9,70,-1);

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    hbox6=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox6);
    gtk_box_pack_start(GTK_BOX(vbox2),hbox6,TRUE,TRUE,0);

    label10=gtk_label_new("");
    gtk_widget_show(label10);
    gtk_box_pack_start(GTK_BOX(hbox6),label10,FALSE,FALSE,0);
    gtk_widget_set_size_request(label10,103,-1);

    button_submit=gtk_button_new_with_mnemonic("submit");
    gtk_widget_show(button_submit);
    gtk_box_pack_start(GTK_BOX(hbox6),button_submit,FALSE,FALSE,0);
    gtk_widget_set_size_request(button_submit,60,-1);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++

    label_warn=gtk_label_new("please remember your infomation");
    gtk_widget_show(label_warn);
    gtk_box_pack_start(GTK_BOX(vbox2),label_warn,FALSE,FALSE,0);
    gtk_widget_set_size_request(label_warn,-1,79);

    wadd.name=GTK_ENTRY(entry_user1);
    wadd.pwd=GTK_ENTRY(entry_pwd1);

    g_signal_connect(G_OBJECT(button_submit),"clicked",G_CALLBACK(func_button_update),(gpointer)&wadd); 

    return window_adduser;
}

//++++++++提交按钮调用函数++++++++++++++++++++++++++++++++++++++++
void func_button_update(GtkWidget *widget,gpointer data)
{
    struct widadd *aa=(struct widadd *)data;
    gchar *name=(gchar *)gtk_entry_get_text(GTK_ENTRY(aa->name));
    gchar *pwd=(gchar *)gtk_entry_get_text(GTK_ENTRY(aa->pwd));

    strcpy(aaddsi.name,name);
    strcpy(aaddsi.pwd,pwd);
    if(fdstatu)
    {
        g_thread_create(G_THREAD_FUNC(go_to),NULL,FALSE,NULL);
        fdstatu=0;
    }
    wriadd=1;
    fanhui_log();

}

//+++++++++++注册以后，返回登录界面+++++++++++++++++++++++++++++++++++++++++++
void fanhui_log(void)
{
    while(1)
    {
        if(add_stut)
        {
            gtk_widget_destroy(window_adduser);
            gtk_widget_show_all(window_login);
            break;
        }
    }
}



//++++++++++++++++（go_to)函数++++++++++++++++++++++++
void go_to(void)
{
    printf("已经进入go_to\n");
    for (i = 0; i < 20; i++) {
        allmess[i].fd = -1;
        allmess[i].tu = 0;
        add[i][0] = -1;
        add[i][1] = -1;
        allmess[i].winstu = 0;
        allmess[i].ac = 1;
    }
    char *token;
    if (top) {
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
            perror("fail to create socket");
        }
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        bzero(&dest,sizeof(dest));
        dest.sin_family=AF_INET;
        dest.sin_port=htons(8000);
        inet_pton(AF_INET,"192.168.0.99",&dest.sin_addr);

        if(connect(sockfd,(struct sockaddr *)&dest,sizeof(dest))==-1)
        {
            perror("Connect");
            exit(errno);
        }
        while (1) {
            FD_ZERO(&allset);
            maxfd = 0;
            FD_SET(sockfd, &allset);
            if (sockfd >maxfd)
                maxfd = sockfd;
            while (wrilog || wriadd || 1 || jinji) {
                char wri[200];
                memset(wri, '\0', 200);
                if (wrilog) {
                    sprintf(wri, "usercheck:%s:%s",alogsi.name, alogsi.pwd);
                    write(sockfd, wri, strlen(wri));
                    wrilog = 0;
                    break;
                }
                if (wriadd) {
                    sprintf(wri, "useradd:%s:%s", aaddsi.name,aaddsi.pwd);
                    printf("%s\n", wri);
                    write(sockfd, wri, strlen(wri));
                    wriadd = 0;
                    break;
                }
                if (jinji) {
                    jinji = 0;
                    break;
                }
            }
            retval = select(maxfd + 1, &allset, NULL, NULL, NULL);
            if (retval == 0) {
                continue;
            } else {
                if (FD_ISSET(sockfd, &allset)) {
                    bzero(buffer, MAXBUF + 1);
                    len = read(sockfd, buffer, MAXBUF);
                    if (len > 0) {
                        printf("%s\n", buffer);
                        token = strtok(buffer, ":");
                        printf("token=%s\n", token);
                        if ((strcmp(token, "sqlfailed"))
                                == 0) {
                            printf("server the mysql =%s\n", token);
                            memset(token, '\0', strlen(token));
                            continue;
                        }
                        if ((strcmp(token, "ucount")) == 0) {
                            token = strtok(NULL, ":");
                            printf("listcount=%s\n", token);
                            listcount = atoi(token);
                            memset(token, '\0', 200);
                            jinji = 1;
                        }
                        if ((strcmp(token, "sigin")) == 0){
                            int x;
                            x = tu_mess();
                            //name
                            token = strtok(NULL, ":");
                            printf("sigin1=%s\n", token);
                            strcpy(allmess[x].name, token);
                            //ip
                            token = strtok(NULL, ":");
                            printf("sigin1=%s\n", token);
                            strcpy(allmess[x].ip, token);
                            //port
                            token = strtok(NULL, ":");
                            printf("sigin1=%s\n", token);
                            strcpy(allmess[x].port, token);
                            //
                            token = strtok(NULL, ":");
                            printf("sigin1=%s\n", token);
                            strcpy(allmess[x].statu, token);
                            allmess[x].tu = 1;
                            memset(token, '\0', 200);
                            jinji = 1;
                        }
                        if ((strcmp(token, "over")) == 0) {
                            log_stut = 1;
                            memset(token, '\0', 200);
                            break;
                        }
                        if ((strcmp(token, "chkoff")) == 0) {
                            printf("用户名或密码不对，或已经登陆过不能重复登陆！\n");
                        }
                        if ((strcmp(token, "on")) == 0) {
                            token = strtok(NULL, ":");
                            add_stut = 1;
                            printf("注册成功！\n");
                            memset(ch_dialog,'\0',100);
                            sprintf(ch_dialog,"请牢记您审请的号码\n\t%s",token);
                            func_dialog();
                        }
                        if ((strcmp(token, "off")) == 0) {
                            printf("注册失败,换ID！\n");
                        }
                    }

                    else {
                        if (len < 0)
                            printf("消息接收失败！错误信息是'%s'\n", errno, strerror(errno));
                        else
                            printf("对方退出了，聊天终止！\n");
                        break;
                    }
                }
                if (FD_ISSET(0, &allset)){
                    bzero(buffer, MAXBUF + 1);
                    fgets(buffer, MAXBUF, stdin);
                    if (!strncasecmp(buffer, "quit", 4)) {
                        printf("自己请求终止聊天！\n");
                        break;
                    }
                    len = send(sockfd, buffer, strlen(buffer) - 1, 0);
                }
            }
        }
        top = 0;
    }
    //++++++++++++开始当服务器使用++++++
    printf("现在进入服务器进行通信\n");
    listfd=socket(AF_INET,SOCK_STREAM,0);
    printf("listfd=%d\n",listfd);
    setsockopt(listfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    printf("SO_REUSEADDR=%d\n", SO_REUSEADDR);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(atoi(allmess[0].port));

    printf("port=%d\n",atoi(allmess[0].port));

    if(bind(listfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
    {    printf("绑定错误\n");
        printf("%s\n",strerror(errno));
        perror("Bind");
        printf("\n");
    }
    listen(listfd,20);
    maxfd=max_fd(listfd,sockfd);
    printf("listfd=%d\n",listfd);
    FD_ZERO(&allset);
    FD_SET(listfd, &allset);
    FD_SET(sockfd, &allset);
    for (;;) {
        printf("!!!!!!!!!!\n");
        nready = select(maxfd + 1,&allset, NULL, NULL, NULL);
        printf("...........\n");
        if (nready < 0)
            printf("select error\n");
        else {
            if (FD_ISSET(listfd, &allset)) {
                int cli = addr();
                add[cli][0] = cli;
                cliaddr_len = sizeof(cliaddr[cli]);
                printf("有连接，连接前\n");
                connfd = accept(listfd, (struct sockaddr *)&cliaddr[cli], &cliaddr_len);
                printf("已有新连接\n");
                add[cli][1] = connfd;
                //add[cli][0] = 1;
                maxfd = max_fd(maxfd, connfd);
                add_sockset(&allset, sockfd, listfd, add);
                char funip[25];
                memset(funip, '\0', 25);
                sprintf(funip, "%s", inet_ntop(AF_INET, &cliaddr[cli].sin_addr, str, sizeof(str)));
                printf("连接我的ip是：%s\n", funip);
                char funport[7];
                memset(funport, '\0', 7);
                sprintf(funport, "%d", ntohs(cliaddr[cli].sin_port));
                printf("连接我的port是：%s\n", funport);
                int a;
                for (a = 0; a < listcount; a++){
                    if ((strcmp(allmess[a].ip, funip) == 0) && (strcmp(allmess[a].port, funport)
                                == 0)) {
                        allmess[a].fd = connfd;
                        printf("allmess[%d].fd=%d\n", a, allmess[a].fd);
                    }
                    break;
                }
                printf("已经有人链接我了fd=%d\n", connfd);
                continue;
            }
            if (FD_ISSET(0, &allset)){
                printf("quit=0\n");
                break;
            }
            if (FD_ISSET(sockfd, &allset)){
                printf("11111\n");
                bzero(buffer, MAXBUF + 1);
                len = read(sockfd, buffer, MAXBUF);
                printf("111112222-buffer=%s\n", buffer);
                printf("222222\n");
                if (len == 0){
                    printf("3333\n");
                    xx = 1;
                    //FD_CLR(sockfd,&allset);
                    //sockfd=-1;
                    printf("44444\n");
                    add_sockset(&allset, sockfd, listfd, add);
                    printf("55555\n");
                    continue;
                }
                token = strtok(buffer, ":");
                if (strcmp(token, "accet") == 0) {
                    printf("accet****\n");
                    add_sockset(&allset, sockfd, listfd, add);
                    continue;
                }
                if (strcmp(token, "delu") == 0){
                    printf("delu****\n");
                    token = strtok(NULL, ":");
                    for (j = 0; j < listcount; j++) {
                        if (strcmp(allmess[j].name, token) == 0){
                            token = strtok(NULL, ":");
                            memset(allmess[j].ip, '\0', 25);
                            strcpy(allmess[j].ip, token);
                            token = strtok(NULL, ":");
                            memset(allmess[j].port, '\0', 10);
                            strcpy(allmess[j].port, token);
                            strcpy(allmess[j].statu, "1");
                            break;
                        }
                    }
                    //更新列表
                    gdk_threads_enter;
                    gtk_list_store_clear((GtkListStore*)store1);
                    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_frend_list), createModel());
                    gdk_threads_leave;
                    add_sockset(&allset, sockfd, listfd, add);
                    continue;
                }
                if ((strcmp(token, "sigin")) == 0) {
                    int x;
                    x = tu_mess();
                    //name
                    token = strtok(NULL, ":");
                    printf("sigin1=%s\n", token);
                    strcpy(allmess[x].name, token);
                    //ip
                    token = strtok(NULL, ":");
                    printf("sigin1=%s\n", token);
                    strcpy(allmess[x].ip, token);
                    //port
                    token = strtok(NULL, ":");
                    printf("sigin1=%s\n", token);
                    strcpy(allmess[x].port, token);
                    //
                    	token = strtok(NULL, ":");
                    	printf("sigin1=%s\n", token);
                    	strcpy(allmess[x].statu, token);
                    allmess[x].tu = 1;
                    listcount++;
                    //更新列表
                    gdk_threads_enter;
                    gtk_list_store_clear((GtkListStore*)store1);
                    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_frend_list), createModel());
                    gdk_threads_leave;
                    continue;
                }
                if (strcmp(token, "quit") == 0){
                    printf("1 buffer=%s\n", token);
                    char aaip[30];
                    memset(aaip,'\0',30);
                    token = strtok(NULL, ":");
                    strcpy(aaip,token);
                    token = strtok(NULL, ":");
                    for (j = 0; j < listcount; j++) {
                        if (strcmp(allmess[j].port,token) == 0 && strcmp(allmess[j].ip,aaip) == 0){
                            strcpy(allmess[j].statu, "0");
                            for (i = 0; i < messcount; i++)
                                if (add[i][0] == allmess[j].fd){
                                    add[i][0] = -1;
                                    add[i][1] = -1;
                                    break;
                                }
                            allmess[j].fd = -1;
                            allmess[j].ac = 1;
                        }
                    }
                    //更新列表
                    gdk_threads_enter;
                    gtk_list_store_clear((GtkListStore*)store1);
                    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_frend_list), createModel());
                    gdk_threads_leave;
                    add_sockset(&allset, sockfd, listfd, add);
                    continue;
                }

                memset(sysmsg, '\0', 1000);
                strcpy(sysmsg,buffer);
                add_sockset(&allset, sockfd, listfd, add);
                printf("aaa buffer=%s\n", buffer);
                continue;
            }
            for (i = 0; i < messcount; i++) {
                printf("i=%d\n",i);
                if ((add[i][0] != -1) && (FD_ISSET(add[i][1], &allset))) {
                    bzero(buffer, MAXBUF + 1);
                    printf("111222aaa\n");
                    readcount = read(add[i][1],buffer, MAXBUF);
                    if (readcount == 0) {
                        for (j = 0; j < listcount; j++) {
                            if (allmess[j].fd == add[i][1]){
                                strcpy(allmess[j].statu, "0");
                                allmess[j].fd = -1;
                                allmess[j].ac = 1;
                                break;
                            }
                        }
                        add[i][0] = -1;
                        add[i][1] = -1;
                        add_sockset(&allset, sockfd, listfd, add);
                        //更新列表
                        gdk_threads_enter;
                        gtk_list_store_clear((GtkListStore*)store1);
                        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_frend_list), createModel());
                        gdk_threads_leave;
                        continue;
                    } else {
                        token = strtok(buffer, ":");
                        if (strcmp(token, "lian") == 0) {
                            token = strtok(NULL, ":");
                            printf("if(lian=%s)\n", token);
                            for (j = 0; j < listcount; j++) {
                                if (strcmp(allmess[j].name, token) == 0) {
                                    allmess[j].fd = add[i][1];
                                    printf("allmess[%d]=%d\n", j, allmess[j].fd);
                                    break;
                                }
                            }
                            add_sockset(&allset, sockfd, listfd, add);
                            continue;
                        }
                        if (strcmp(token, "file") == 0) {

                            continue;
                        }
                        if (strcmp(token, "#f") == 0){
                            continue;
                        }
                        for (j = 0; j < listcount; j++) {
                            if (allmess[j].fd == add[i][1]) {
                                printf("%s的%d来信息是%s\n",allmess[j].name,allmess[j].fd,buffer);
                                if (allmess[j].winstu) {
                                    gdk_threads_enter();
                                    memset(amsg.msg, '\0', 1000);
                                    sprintf(amsg.msg, "%s:     ", allmess[j].name);
                                    strcat(amsg.msg, buffer);
                                    amsg.xb = j;
                                    combochange_log(amsg.xb, amsg.msg);
                                    gdk_threads_leave();
                                    //add_sockset(&allset, sockfd, listfd, add);
                                    break;
                                } else {
                                    g_thread_create(G_THREAD_FUNC(func_action), (void *)j, FALSE, NULL);
                                    usleep(20000);
                                    gdk_threads_enter();
                                    memset(amsg.msg, '\0', 1000);
                                    sprintf(amsg.msg, "%s:     ", allmess[j].name);
                                    strcat(amsg.msg, buffer);
                                    amsg.xb = j;
                                    combochange_log(amsg.xb, amsg.msg);
                                    gdk_threads_leave();
                                    break;
                                }
                            }
                        }
                        printf("acsbuffer=%s\n", buffer);
                        add_sockset(&allset, sockfd, listfd, add);
                        break;
                    }
                }
            }
        }
    }
    close(sockfd);
}





//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void add_sockset(fd_set *sockset,int sockfd,int user_link,int add[messcount][2])
{
    int i;
    FD_ZERO(sockset);
    if(xx)
        FD_CLR(sockfd,&allset);
    else
        FD_SET(sockfd,sockset);
    FD_SET(user_link,sockset);
    FD_SET(1,sockset);
    for(i=0;i<messcount;i++)
    {
        if(add[i][0]!=-1)
            FD_SET(add[i][1],sockset);
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int addr(void)
{
    int i;
    for(i=0;i<messcount;i++)
        if(add[i][0]==-1)
            return i;

}
//+++++++++++++++++++++++++++++++++++++++++++++++++

int tu_mess(void)
{
    int i;
    for(i=0;i<messcount;i++)
        if(allmess[i].tu==0)
            return i;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
int max_fd(int ab,int ac)
{
    if(ab>ac)
        return ab;
    else
        return ac;
}

//++++++++++++++++++++++++++++++++++++++++++

void func_close(void)
{
    close(sockfd);
    for(i=0;i<messcount;i++)
    {
        if(add[i][0]!=-1)
            close(add[i][1]);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++

void on_delete_event(GtkWidget *widget,gpointer date)
{
    printf("aaaaaaaaaaaaaa\n");
    func_close();
    gtk_main_quit();
    exit(0);

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void close_win(GtkWidget *widget,gpointer date)
{
    gtk_widget_destroy(window1);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GtkWidget *func_dialog1(void)
{
    GtkWidget *vbox1;
    GtkWidget *label_ti;
    GtkWidget *hbox1;
    GtkWidget *label2;
    GtkWidget *button1;
    window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window1,198,128);
    gtk_window_set_title(GTK_WINDOW(window1),"window1");
    gtk_window_set_resizable(GTK_WINDOW(window1),FALSE);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(window1),TRUE);
    vbox1=gtk_vbox_new(FALSE,0);
    gtk_widget_show(vbox1);
    gtk_container_add(GTK_CONTAINER(window1),vbox1);

    label_ti=gtk_label_new(ch_dialog);
    gtk_widget_show(label_ti);
    gtk_box_pack_start(GTK_BOX(vbox1),label_ti,FALSE,FALSE,0);
    gtk_widget_set_size_request(label_ti,38,98);

    hbox1=gtk_hbox_new(FALSE,0);
    gtk_widget_show(hbox1);
    gtk_box_pack_start(GTK_BOX(vbox1),hbox1,TRUE,TRUE,0);

    label2=gtk_label_new("");
    gtk_widget_show (label2);
    gtk_box_pack_start (GTK_BOX (hbox1), label2, FALSE, FALSE, 0);
    gtk_widget_set_size_request (label2, 136, 0);

    button1 = gtk_button_new_with_mnemonic (" 确 定 ");
    gtk_widget_show (button1);
    gtk_box_pack_start (GTK_BOX (hbox1), button1, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(close_win),(gpointer)&window1);

    return window1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++

void func_dialog(void)
{
    GtkWidget* aaa;
    aaa=func_dialog1();
    gtk_widget_show (aaa);
}

//++++++++++++++++++++聊天信息显示++++++++++++++++++++++++

void combochange_log(int fs, char *msg)
{
    GtkTextIter iter;
    GString *order_string;
    GtkTextMark *tmp_mark;

    gtk_text_buffer_get_end_iter(allmess[fs].buffer_up, &iter);
    gtk_text_buffer_insert(allmess[fs].buffer_up, &iter,msg, -1);

    printf("123456789=%s\n",msg);
    order_string = g_string_new("\n");
    gtk_text_buffer_insert(allmess[fs].buffer_up, &iter, order_string->str, -1);
    g_string_free(order_string, TRUE);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++

void go_to_broadcast(int aas)
{
    char *text;
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(allmess[aas].buffer_down), &start, &end);	/*获得缓冲区开始和结束位置的Iter */
    const GtkTextIter s = start, e = end;
    text = (char *)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(allmess[aas].buffer_down), &s, &e, FALSE);	/*获得文本框缓冲区文本 */
    gdk_threads_enter();
    memset(amsg.msg, '\0', 1000);
    sprintf(amsg.msg, "%s:     ", allmess[0].name);
    strcat(amsg.msg, text);
    amsg.xb = aas;
    combochange_log(amsg.xb, amsg.msg);
    gdk_threads_leave();
}

//+++++++++++++++创建与好友的连接++++++++++++++++++++++++++++++++++++++

int accect_to(int w)
{
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("sock=%d\n", sock);

    int b = addr();
    add[b][0] = b;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&cliaddr[b], sizeof(cliaddr[b]));
    cliaddr[b].sin_family = AF_INET;
    cliaddr[b].sin_port = htons(atoi(allmess[w].port));
    inet_pton(AF_INET, allmess[w].ip, &cliaddr[b].sin_addr);
//    inet_aton(allmess[w].ip, (struct in_addr *)&cliaddr[b].sin_addr.s_addr);
    /* 连接客户端 */
    printf("要链接的客户IP是：%s\n", allmess[w].ip);
    printf("要链接的客户PORT是：%s\n", allmess[w].port);
    if (connect(sock, (struct sockaddr *)&cliaddr[b], sizeof(cliaddr[b])) == 0){
        add[b][1] = sock;
        maxfd = max_fd(maxfd, sock);
        allmess[w].fd = sock;

        add_sockset(&allset, sockfd, listfd, add);
        char aaa[30];
        memset(aaa, '\0', 30);
        sprintf(aaa, "lian:%s", allmess[0].name);
        int cou;
        cou=strlen(aaa);

        printf("aaa11=%s", aaa);
        write(sock,aaa,strlen(aaa));

        memset(aaa, '\0', 30);
        sprintf(aaa, "accet");
        write(sockfd, aaa, strlen(aaa));
    }
    else{
        perror("Connect ");
 	
    }
}

//+++++++++++++++发送消息++++++++++


void wri_to(GtkWidget * widget, gpointer data)
{
    int ss = (int)data;
    char *text;
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(allmess[ss].buffer_down), &start, &end);	/*获得缓冲区开始和结束位置的Iter */
    const GtkTextIter s = start, e = end;
    text = (char *)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(allmess[ss].buffer_down), &s, &e, FALSE);	/*获得文本框缓冲区文本 */
/****************************
	oneonesafe add by 2012 4.24
************************************/

    printf("%s\n",text);
    if (strlen(text) != 0){
        printf("go_to_broadcase\n");
        g_thread_create(G_THREAD_FUNC(go_to_broadcast),(void *)ss, FALSE, NULL);
    }
    write(allmess[ss].fd, text,strlen(text));
    printf("向%s的%d发送的信息是%s\n",allmess[ss].name,allmess[ss].fd,text);
}

//+++++++++++++++对话框退出事件++++++++++++

void delete_event(GtkWidget * widget, GdkEvent * event, gpointer data)
{
    int ss = (int)data;
    allmess[ss].winstu = 0;
    gtk_widget_destroy(widget);
}

//++++++++++++++++创建对话框++++++++++++++++
void func_action(int h)
{
    gdk_threads_enter();
    printf("allmess_func_111[%d].wintu＝%d\n", h, allmess[h].winstu);
    if (!allmess[h].winstu) {

        if (allmess[h].fd == -1) {
            accect_to(h);
        }
        printf("allmess.fd=%d\n", allmess[h].fd);

        printf("allmess_func_222[%d].wintu＝%d\n", h, allmess[h].winstu);
        GtkWidget *to_to;
        allmess[h].winstu = 1;
        to_to = create_toto(h);

        printf("allmess_func_333[%d].wintu＝%d\n",h, allmess[h].winstu);
    }
    gdk_threads_leave();
}

//++++++++++++++++对话框++++++++++++++++
void destroy(GtkWidget * widget, gpointer * data)
{

    gtk_widget_destroy(GTK_WIDGET(data));

}

void dialog(GtkWidget * widget, gpointer * data)
{
    gdk_threads_enter();

    GtkWidget *dialog;

    GtkWidget *label;

    gchar *title;

    dialog = gtk_dialog_new();

    label = gtk_label_new(NULL);

    title = "<span foreground=\"red\"><big>\n提示：\n\n该用户没有登陆，不能对其说话！！\n</big></span>";

    gtk_label_set_markup(GTK_LABEL(label), title);

    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), label, TRUE, TRUE, 0);

    gtk_widget_show(label);

    gtk_widget_show(dialog);

    gdk_threads_leave();

}

//++++++++++++++++选择事件++++++++++++++++
gboolean selection_changed(GtkWidget * widget, gpointer data)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *value;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) {
        gtk_tree_model_get(model, &iter, 1, &value, -1);
        printf("%s\n", value);
        int i;
        for (i = 0; i < listcount; i++){
            if (strcmp(allmess[i].name, value) == 0) {

                if (atoi(allmess[i].statu) == 0) {
                    g_thread_create(G_THREAD_FUNC(dialog), NULL, FALSE, NULL);
                    break;
                } else {
                    g_thread_create(G_THREAD_FUNC(func_action), (void *)i, FALSE, NULL);
                    break;
                }
            }
        }

    }
}

//++++++++++++++++好友列表+++++++++++++++++
GtkTreeModel *createModel()
{
    int unline;
    int online;

    const gchar *files[] = { "emoticon2.ico"};

    const gchar *file[] = { "emoticon3.ico"};

    GtkWidget *cellView;
    GtkTreeIter iter1, iter2;
    gint i, j, s, k = 0;

    char ag[2]="";
    char line[2][20];
    int a1=1;
    int a2=1;
    memset(line, 0, 40);
    strcpy(line[0], "在线好友");
    strcpy(line[1], "不在线好友");

    store1 = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
    cellView = gtk_cell_view_new();
    for (i = 0; i < 2; i++) {
        gtk_tree_store_append(store1, &iter1, NULL);
        gtk_tree_store_set(store1, &iter1, PIXBUF_COL,ag, TEXT_COL, line[i], -1);
        if (i == 0) {
            for (j = 1; j < listcount; j++) {
                    printf("+++++++++\n");
                if (atoi(allmess[j].statu) == 1) {
                    printf("在线循环：%d次\n",j);
                    a1=0;
                    s = rand() % 5;
                    gtk_tree_store_append(store1, &iter2, &iter1);
                    gtk_tree_store_set(store1, &iter2, PIXBUF_COL,ag, TEXT_COL, allmess[j].name, -1);
                    printf("%s\n", allmess[j].name);
                }
            }
            if(a1){
                gtk_tree_store_append(store1, &iter2, &iter1);
                gtk_tree_store_set(store1, &iter2, PIXBUF_COL,ag, TEXT_COL,"无人上线", -1);
                continue;
            }
        } else {
            for (j = 0; j < listcount; j++) {
                if (atoi(allmess[j].statu) == 0) {
                    s = rand() % 5;
                    a2=0;
                    gtk_tree_store_append(store1, &iter2, &iter1);
                    gtk_tree_store_set(store1, &iter2, PIXBUF_COL,ag, TEXT_COL, allmess[j].name, -1);
                    printf("%s\n", allmess[j].name);
                }
            }
            if(a2){
                gtk_tree_store_append(store1, &iter2, &iter1);
                gtk_tree_store_set(store1, &iter2, PIXBUF_COL,ag, TEXT_COL,"无人离线", -1);
            }
        }
    }
    return GTK_TREE_MODEL(store1);
}

//++++++++++++++++++创建好友列表++++++++++++++++++++++++++++
GtkWidget *create_list(void)
{
    GtkWidget *window_clicked;
    GtkWidget *vbox2;
    GtkWidget *label_top;
    GtkWidget *scrolledwindow1;
    GtkWidget *label_end;

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    GtkTreeModel *model;
    GtkTreeSelection *selection;

    window_clicked = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_clicked, 241, 540);
    gtk_window_set_title(GTK_WINDOW(window_clicked), "聊天工具客户端");
    gtk_window_set_resizable(GTK_WINDOW(window_clicked), FALSE);
    gtk_window_set_icon_name(GTK_WINDOW(window_clicked), "stock_smiley-1");
    gtk_window_set_position(GTK_WINDOW(window_clicked), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window_clicked), "delete_event", G_CALLBACK(on_delete_event), NULL);

    vbox2 = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox2);
    gtk_container_add(GTK_CONTAINER(window_clicked), vbox2);
    char baoti[100];
    memset(baoti, '\0', 100);
    sprintf(baoti, " %s 您好,欢迎您登陆.", allmess[0].name);
    label_top = gtk_label_new(baoti);
    gtk_widget_show(label_top);
    gtk_box_pack_start(GTK_BOX(vbox2), label_top, FALSE, FALSE, 0);

    scrolledwindow1 = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_show(scrolledwindow1);
    gtk_box_pack_start(GTK_BOX(vbox2), scrolledwindow1, TRUE, TRUE, 0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolledwindow1), GTK_SHADOW_IN);


    treeview_frend_list = gtk_tree_view_new();
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_frend_list),(GtkTreeModel *) createModel());

    gtk_widget_show(treeview_frend_list);
    gtk_container_add(GTK_CONTAINER(scrolledwindow1), treeview_frend_list);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("QQ", renderer, "text", PIXBUF_COL, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview_frend_list), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("好友列表", renderer, "text", TEXT_COL, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview_frend_list), column);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_frend_list));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview_frend_list));
    g_signal_connect(G_OBJECT(selection), "changed", G_CALLBACK(selection_changed), model);

    time_t now;
    struct tm *l_time;
    gchar buf[100];
    now=time((time_t *)NULL);
    l_time=localtime(&now);
    sprintf(buf,"多人聊天工具，登陆时间是  %d:%d:%d",l_time->tm_hour,l_time->tm_min,l_time->tm_sec);
    label_end = gtk_label_new(buf);
    gtk_widget_show(label_end);
    gtk_box_pack_start(GTK_BOX(vbox2), label_end, FALSE, FALSE, 0);
    return window_clicked;
}
//++++++++++++++++++消息对话框退出事件++++++++++++++++++++++++++++
void button_klose(GtkWidget * widget, gpointer *date)
{
    struct close *clo=(struct close *)date;
    printf("+++++++close=%d\n",clo->cl);
    gtk_widget_destroy(clo->wcl);
    allmess[clo->cl].winstu=0;
}
//++++++++++++++++++消息对话框++++++++++++++++++++++++++++
GtkWidget *create_toto(int h)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *list1;
    GtkWidget *label2;
    GtkWidget *list2;
    GtkWidget *label3;
    GtkWidget *button_send;
    GtkWidget *button_close;
    GtkWidget *table;

    GdkColor color;
    color.red = 0x9e00;
    color.green = 0xcf00;
    color.blue = 0xff00;   

    GtkWidget *scrolledwindow1;
    char acp[100];
    sprintf(acp, "%s正在与 %s 进行对话聊天",allmess[0].name, allmess[h].name);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_set_size_request(window, 401, 350);
    gtk_window_set_title(GTK_WINDOW(window), acp);
    gtk_container_set_border_width(GTK_CONTAINER(window),3);
    gtk_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(delete_event), (gpointer) h);

    gtk_widget_modify_bg(window,GTK_STATE_NORMAL, &color);

    table = gtk_table_new(9, 10, TRUE);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_widget_show(table);


    list1 = gtk_text_view_new();
    gtk_table_attach_defaults(GTK_TABLE(table), list1, 0, 10, 1, 5);
    gtk_widget_show(list1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(list1), FALSE);

    label2 = gtk_label_new("");
    gtk_table_attach_defaults(GTK_TABLE(table), label2,0,4, 5, 6);
    gtk_widget_show(label2);

    scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_show (scrolledwindow1);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

    list2 = gtk_text_view_new();
    gtk_table_attach_defaults(GTK_TABLE(table), list2, 0, 10, 6, 8);
    gtk_widget_show(list2);

    gtk_container_add (GTK_CONTAINER (scrolledwindow1),list2);

    gtk_table_attach_defaults(GTK_TABLE(table),scrolledwindow1, 0, 10, 6, 8);
    //++++++++++++++
    label3 = gtk_label_new("");
    gtk_table_attach_defaults(GTK_TABLE(table), label3, 0, 6, 8, 9);
    gtk_widget_show(label3);

    button_send = gtk_button_new_with_mnemonic(" 发送(_s) ");
    gtk_table_attach_defaults(GTK_TABLE(table), button_send, 6, 8, 8, 9);
    gtk_widget_show(button_send);

    button_close = gtk_button_new_with_mnemonic(" 关闭(_c) ");
    gtk_table_attach_defaults(GTK_TABLE(table), button_close, 8, 10, 8, 9);
    gtk_widget_show(button_close);

    allmess[h].listup = list1;
    allmess[h].listdown = list2;
    allmess[h].buffer_up = gtk_text_view_get_buffer(GTK_TEXT_VIEW(list1));
    allmess[h].buffer_down = gtk_text_view_get_buffer(GTK_TEXT_VIEW(list2));

    struct close klose;
    klose.wcl=window;
    klose.cl=h;

    gtk_signal_connect(GTK_OBJECT(button_send), "clicked", GTK_SIGNAL_FUNC(wri_to),(gpointer) h);
    gtk_signal_connect(GTK_OBJECT(button_close), "clicked", GTK_SIGNAL_FUNC(button_klose),(gpointer)&klose);

    gtk_widget_show_all(window);

    gtk_main();

    return window;
}

