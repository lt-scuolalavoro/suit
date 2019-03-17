gcc src/cgi/users.c -o www/new/cgi/users.cgi `mysql_config --libs --cflags`
gcc src/cgi/user.c -o www/new/cgi/user.cgi `mysql_config --libs --cflags`
gcc src/cgi/main.c -o www/new/cgi/main.cgi `mysql_config --libs --cflags`
gcc src/cgi/addCandidate.c -o www/new/cgi/addCandidate.cgi `mysql_config --libs --cflags`
