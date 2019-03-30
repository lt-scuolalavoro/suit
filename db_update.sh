#!/bin/bash
cd src/sql
#File counter
f=$(ls -q | wc -l);

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

echo "You are currently at version $v"

if [ "$v" != "$f" ]; then
	#Execute the command for every .sql file
	for (( c=v+1; c<=f; c++ ))
	do  
		#Execute the v.sql
		mysql -u root < v$c.sql
	done
fi

echo ""
echo "Updated to version $f"
