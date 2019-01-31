# Suit
This app will keep track of all the __HR__ components of the company, storing in a database name, surname, birth date and some other basic informations of the candidate.

## Wiki
To access the wiki of this software, click [here](https://github.com/lt-scuolalavoro/suit/wiki).

## Clone the repository
__Clone the project in your home directory__ by using the following command in the terminal:
```
cd ~ && git clone https://github.com/lt-scuolalavoro/suit.git
```
## Compile and run
In __suit__ folder:
1. Compile:\
```gcc -o bin/suit src/candidates.c```    
2. Run:\
```bin/suit```

__Compile main CGI:__
```gcc src/cgi/main.c -o www/cgi/main.cgi `mysql_config --cflags --libs```

__MySQL programs:__
1. Compile:\
```gcc -o bin/[name].exe src/mysql/[file name] `mysql_config --cflags --libs` ```
2. Run:\
```sudo bin/[name].exe```

## Useful docs 
* [MySQL C](https://docs.google.com/document/d/1XyP09J5EF2wkSpmlwJ9Ew7IGDa0sb1mDyL_xx6XuTk8/edit) - MySQL C API programming tutorial
 
## Built with
* C
* MySQL
