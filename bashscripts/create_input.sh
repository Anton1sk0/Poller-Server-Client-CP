#!/bin/bash


FILE="$1"
LINESS="$2" #To lines einai desmeumenh leksh mou phre mish wra na to vrw 
randchar="abcdefghjklmnopqrstuvwsyz"

if [[ "$#" -ne 2 ]]; then
	echo "Not valid arguments, call the script like this ./create_input.sh politicalParties.txt numLines"
	exit
fi

if [[ ! -f "$FILE" ]]; then 
	echo "File "$FILE"  cannot be opened"
	exit
fi

if [[ !("$LINESS" =~ ^[0-9]+$) ]]; then
	echo "Second argument is not an integer"
	exit
fi
# echo "exei $LINESS grammes" 
touch inputFile #creating the file 




for   ((i=1; i<=$LINESS; i++))

do
	length=$(( RANDOM % 8 + 5 ))  # Random length between 5 and 12

	# echo "twra vriskomai sth $i loopa /n"
	# echo "to lines einai $LINESS"
	shuffledword=$(shuf $FILE | head -n 1)
	name=""
	for((j=1; j<length; j++))
	do
		random_index=$(( RANDOM % ${#randchar} )) #rand length of randchar
		name=$name${randchar:random_index:1} #add rand letter 
	
	done
	surname=""
	length=$((RANDOM % 8+5))      #surname differend length of name to be more realistic
	for((j=1;j<length;j++))
	do
		random_index=$(( RANDOM % ${#randchar} )) 
		surname=$surname${randchar:random_index:1} 
	done
	echo "${name}" "${surname}" "${shuffledword}">>inputFile
done

