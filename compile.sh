gcc src/cgi/users.c -o www/cgi/users.cgi `mysql_config --libs --cflags`
gcc src/cgi/user.c -o www/cgi/user.cgi `mysql_config --libs --cflags`
gcc src/cgi/main.c -o www/cgi/main.cgi `mysql_config --libs --cflags`
