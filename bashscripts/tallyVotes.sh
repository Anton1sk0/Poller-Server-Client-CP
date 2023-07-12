#!/bin/bash

input_file="inputFile"
temp_file="tempFile"
result_file="$1"



if [[ "$#" -ne 1 ]]; then
        echo "Not valid arguments, call the script like this ./tallyVotes.sh tallyResultsFile"
        exit
fi


if [[ ! -f inputFile || ! -e inputFile ]]; then
        echo "inputFile is not exist or cannot be opened"
        exit
fi

if [[ ! -r inputFile ]]; then
        echo "inputFile is not readable, please change the permission"
        exit
fi

input_file="inputFile"
temp_file="tempFile"
result_file="$1"

awk '!seen[$1,$2]++' "$input_file" > "$temp_file" #to idio atomo p exei psifisei 2 fores to afairw apo tous psififorous, etsi kai alliws mono provlhmata dhmiourgei kai krataw mono ton prwto
mv "$temp_file" "$input_file"

###############
###############


file="inputFile"
lines_of_file=$(wc -l < "$file")

cut -d ' ' -f 3 "$file" | while read -r word; do #3 giati to nea_dhmokratia p.x exei keno
if [ -z "$word" ]; then
	continue
fi   #to skip emtpy lines


psifoi=$(cat "$file" | grep -w "$word" | wc -l) #for every komma count, tha mporousa na xrhsimopoihsw kai uniq -c alla to ekana etsi twra 
echo "$word" "$psifoi" 

done | sort | uniq > "$result_file" #to uniq thelei prwta sort giati alliws kati pathainei me ta kena kai failarei


