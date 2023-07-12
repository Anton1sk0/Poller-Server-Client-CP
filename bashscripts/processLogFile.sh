#!/bin/bash

input_file="$1"
temp_file="tempFile"

if [[ "$#" -ne 1 ]]; then
        echo "Not valid arguments, call the script like this ./processLogFile.sh poll-log"
        exit
fi
 

if [[ ! -f "$input_file" || ! -e "$input_file" ]]; then
        echo ""$1" is not exist or cannot be opened"
        exit
fi

if [[ ! -r "$input_file" ]]; then
        echo ""$input_file" is not readable, please change the permission"
        exit
fi

awk '!seen[$1,$2]++' "$input_file" > "$temp_file" #to idio atomo p exei psifisei 2 fores to afairw apo tous psififorous, etsi kai alliws mono provlhmata dhmiourgei kai krataw mono ton prwto
mv "$temp_file" "$input_file"
###############
###############
###############

file="$1"
lines_of_file=$(wc -l < "$file")

cut -d ' ' -f 3-4 "$file" | while read -r word; do #3-4 giati to nea dhmokratia p.x exei keno

psifoi=$(cat "$file" | grep -w "$word" | wc -l) #for every komma count, tha mporousa na xrhsimopoihsw kai uniq -c alla to ekana etsi twra 
if [ -z $"word" ]; then
	continue
fi
echo "$word" "$psifoi" 

done | sort | uniq > pollerResultsFile #to uniq thelei prwta sort giati alliws kati pathainei me ta kena kai failarei

