#!/bin/bash

#########################
# The command line help #
#########################

create_db(){
    mysql -u root -e "CREATE DATABASE IF NOT EXISTS suit;"
}

check_everything () {
    if [ "$1" == "-e" -o "$1" == everything ]; then
        #true
        return 1
    else
        #false
        return 0
    fi
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

#boolean to check if the user have wrong the pharameter
check_invalid_phar=1

#Show the man of ./update.sh
if [ "$1" == "--help" ]; then
    man ./update
fi

#Check if the user wants to do all the options
check_everything $1
#$? catch the last thing that happened, in this case the return of check_everything
EV=$?

if [ "$EV" == "1" ]; then
    cecho "YELLOW" "Updating everything..."
    echo ""
fi

#Show the database version
if [ "$1" == "-dbv" -o "$1" == "--dbversion" ]; then
    check_invalid_phar=0

    v=$(echo "SELECT * FROM version " | mysql suit -u root 2> /dev/null )
    v="$(echo $v | tr -dc '0-9')"

    if [ -z "$v" ]; then
         v=0;
    fi

    echo "Database version : $v."
    echo ""
fi

#Delete the database
if [ "$1" == "-d" -o "$1" == "--drop" ]; then
    check_invalid_phar=0

    mysql -u root -e "DROP DATABASE IF EXISTS suit;"
    cecho "YELLOW" "Database suit deleted."
    echo ""
fi

#Update the database
if [ "$1" == "-db" -o "$1" == "--database" -o "$EV" == "1" ]; then
    check_invalid_phar=0

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
            cecho "RED" "$v"
            cecho "GREEN" "to version $f."

            else
                echo "Database already up to date."
        fi
        echo ""
fi

#Compile CGI
if [ "$1" == "-cgi" -o "$EV" == "1" ]; then
    check_invalid_phar=0

    cecho "YELLOW" "Compiling cgi ..."
        for file in src/cgi/*;
        do
            gcc $file -o www/new/cgi/$(basename "$file")gi `mysql_config --libs --cflags`
        done
        cecho "GREEN" "Cgi compiled successfully."
        echo ""
fi

if [ "$check_invalid_phar" == 1 ]; then
    cecho "RED" "Insert the correct argument. Use man ./update"
    echo ""

    exit 0
fi

#The argument of .sh will called with number [ arg1 = 1, arg2 = 2, etc.]