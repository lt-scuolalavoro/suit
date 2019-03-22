gcc src/cgi/candidates.c -o www/new/cgi/candidates.cgi `mysql_config --libs --cflags`
gcc src/cgi/candidate.c -o www/new/cgi/candidate.cgi `mysql_config --libs --cflags`
gcc src/cgi/main.c -o www/new/cgi/main.cgi `mysql_config --libs --cflags`
gcc src/cgi/addCandidate.c -o www/new/cgi/addCandidate.cgi `mysql_config --libs --cflags`
gcc src/cgi/removeCandidate.c -o www/new/cgi/removeCandidate.cgi `mysql_config --libs --cflags`
