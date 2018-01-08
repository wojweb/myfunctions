#!/bin/bash

address="$(curl -s -X GET http://thecatapi.com/api/images/get?format=xml \
| xmllint --xpath 'string(//url)' -)"

curl -s "$address" -o obraz.img
img2txt obraz.img  

rm obraz.img 

echo 

curl  -s -H "Accept : application/json" -H "Content-Type: application/json" -X GET http://api.icndb.com/jokes/random \
|  jq .value.joke
