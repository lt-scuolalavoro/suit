#!/bin/bash

#########################
# The command line help #
#########################
display_help() {
    echo "Usage: $0 [option...] {start|stop|restart}" >&2
    echo
    echo "   -e, --everything         Update everything "
    echo "   -cdb, --createdb              Create the database "
    echo "   -db, --database             Update the database "
    echo "   -cgi              Compile CGI "
    echo "   -d, --drop              Delete the database "
    echo "   -dbv, --dbversion             Get the database version "
    echo
    # echo some stuff here for the -a or --add-options 
    exit 1
}

create_db(){
    mysql -u root -e "CREATE DATABASE IF NOT EXISTS suit;"
    exit 1
}

#Function to color phrase 
cecho(){
    RED="\033[0;31m"
    GREEN='\033[0;32;1m'
    YELLOW='\033[1;33m' #Light Green
    # ... ADD MORE COLORS
    NC='\033[0m' #No Color
    
    printf "${!1}${2} ${NC}\n"
}

clear

#The argument of .sh will called with number [ arg1 = 1, arg2 = 2, etc.]
case $1 in
    "-h" | "--help")

        display_help

    ;;

    "-dbv" | "-dbversion")
        v=$(echo "SELECT * FROM version " | mysql suit -u root 2> /dev/null )
        v="$(echo $v | tr -dc '0-9')"

        if [ -z "$v" ]; then
            v=0;
        fi

        echo "Database version : $v."
    ;;

    "-d" | "-drop")
        mysql -u root 2> /dev/null < DROP DATABASE suit;
        echo "Database suit deleted."
    ;;

    "-cdb" | "--createdb")

        create_db
        cecho "GREEN" "Database created."

    ;;

    "-e" | "--everything")

        cecho "YELLOW" "Updating everything..."
        echo ""

    ;;&

    "-db" | "--database" | "-e" | "--everything")

        #File counter
        f=$(ls sql -q | wc -l);
        
        create_db

        #Get version from tables
        #We can use 2> /dev/null to suppress the output error
        #If the database doesn't exists it return an error and for this reason we delete the error message
        v=$(echo "SELECT * FROM version " | mysql suit -u root 2> /dev/null )
        
        #Get only the number
        v="$(echo $v | tr -dc '0-9')"
        
        #If v is null/empty set v to 0
        if [ -z "$v" ]; then
            v=0;
        fi
        
        if [ "$v" != "$f" ]; then
            #Execute the command for every .sql file
            for (( c=v+1; c<=f; c++ ))
            do
                #Execute the v.sql
                mysql suit -u root < sql/v$c.sql
            done

            #TODO rimuovere l'andata a capo
            cecho "GREEN" "Database updated from version" -n 
            cecho "RED" " $v"
            cecho "GREEN" "to version $f."

            else
                echo "Already up to date."
        fi

        echo ""

    ;;&
    
    "-cgi" | "-e" | "--everything")    
        cecho "YELLOW" "Compiling cgi ..."
        for file in src/cgi/*;
        do
            gcc $file -o www/new/cgi/$(basename "$file")gi `mysql_config --libs --cflags`
        done
        cecho "GREEN" "Cgi compiled successfully."
    ;;
    *) 
        cecho "RED" "Insert the correct argument. Use -h to see all the command"
    ;;
esac

echo ""