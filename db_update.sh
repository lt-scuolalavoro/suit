#!bin/bash

cd src/sql
#File counter
f=$(ls -q | wc -l);
v=$(echo "SELECT db_version FROM version" | mysql suit -u root)
v="$(echo $v | tr -dc '0-9')"

#$str1 = 'sudo mysql < src/sql/v'
if [ -z "$v" ]; then
	v=0;
fi

for (( c=v; c=f; c++ ))
do  
   	$(echo "mysql < v$c.sql")
done

echo "$f"
echo "$v"
echo "$c"