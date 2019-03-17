#!/bin/bash
cd src/sql
#File counter
f=$(ls -q | wc -l);
v=$(echo "SELECT db_version FROM version" | mysql suit -u root)
v="$(echo $v | tr -dc '0-9')"

#File counter
f=$(ls -q | wc -l);

#Get version from tables
#&> Reinderizza lo standard error nel "buco nero di linux"
#If the database doesn't exists it return an error and for this reason we delete the error message
v=$(echo "SELECT db_version FROM version" | mysql suit -u root &> /dev/null)

#Get only the number
v="$(echo $v | tr -dc '0-9')"

#If v is null/empty set v to 1
if [ -z "$v" ]; then
	v=0;
fi

echo "You are currently at version $v"

#Execute the command for every .sql file
for (( c=v+1; c<=f; c++ ))
do  
	#Execute the v.sql
	mysql -u root < v$c.sql
done

echo ""
echo "Updated to version $f"
