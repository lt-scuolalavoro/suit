#!/bin/bash

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
    "--help")

        echo "-e : Update everything"
        echo "-cdb : Create database" 
        echo "-db : Update database"
        echo "-cgi : Compile cgi"
        echo "-drop : Delete database"
        echo ""

    ;;

    "-e")

        cecho "YELLOW" "Updating everything..."
        echo ""

    ;;&

    "-cdb"|"-e")

        mysql -u root -e "CREATE DATABASE IF NOT EXISTS suit;"

    ;;&

    "-db"|"-e")

        #File counter
        f=$(ls sql -q | wc -l);
        
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
            cecho "GREEN" "Database updated from version" 
            cecho "RED" " $v"
            cecho "GREEN" "to version $f."

            else
                echo "Already up to date."
        fi

        echo ""

    ;;&
    
    
    2|1)
        cecho "YELLOW" "Updating database..."
        #If sql is in src folder, move them in suit
        if [ -d "src/sql" ]; then
            mv src/sql ./
        fi
    ;;&
    
    3|1)    
        cecho "YELLOW" "Compiling cgi ..."
        for file in src/cgi/*;
        do
            gcc $file -o www/new/cgi/$(basename "$file")gi `mysql_config --libs --cflags`
        done
        cecho "GREEN" "Cgi compiled successfully."
    ;;
    *) ;;
esac

echo ""