这是一个具有界面的一个即时聊天软件，功能很简单，只有聊天
这是我本科的毕业设计，很水的一个东西，只是做个纪念

1.由于makefile文件已经写好，所以把程序拷到相应的机器上make一下就编译链接成功，便可以执行了。

2.在编译前要确保服务器有mysql数据库的支撑，客户端有gtk+2.0的支撑。

3.客户端要将程序中要链接的ip改成服务器的真实ip。

4.mysql数据库的安装

5.gtk安装

6.创建Myqq数据库，在Myqq数据库中创建表Usermsg
  username	Varchar(20)
  userpwd	Varchar(20)
  userip	Varchar(20)
  userport	Varchar(10)
  userstatu	Int(2)
