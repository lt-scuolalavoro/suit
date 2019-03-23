#!/bin/bash

for file in src/cgi/*;
do
    gcc $file -o www/new/cgi/$(basename "$file")gi `mysql_config --libs --cflags`
done
