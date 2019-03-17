#!bin/bash
cd src/sql

f = ls -q | wc -l;
v = inserire versione corrente

for v in f : do
	sudo mysql < src/sql/v+1.sql    fare in modo di inserire il valore della v
done


