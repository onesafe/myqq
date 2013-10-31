all :server
CC=gcc
server:server.c
	$(CC) -lpthread server.c global.h -o server `mysql_config --cflags --libs` -I /usr/local/mysql/include/mysql -L /usr/local/mysql/lib/mysql
