#!/bin/bash
for file in * 
do
	IFS=$'\n'
	mv "$file" echo "$file" | gawk -F '\n' '{print tolower($1)}'
done
