#!/usr/bin/env bash

RESET=$(tput sgr0) #resets all set attributes such as color
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
CYAN='\033[1;36m'
BLUE='\033[1;34m'

CC=c++
CFLAGS='-Wall -Wextra -Werror'
RM='rm -rf'
LOG=error.log
OUT_DIR=output

STACK_DIR=stack
STD_STACK=std_stack
FT_STACK=ft_stack

VEC_DIR=vector
STD_VEC=std_vector
FT_VEC=ft_vector

MAP_DIR=map
STD_MAP=std_map
FT_MAP=ft_map

check_compilation_status() 
{
	if [ -s $LOG ]; then
		echo -e $RED"Compilation error, check $LOG for more details"$RESET
	else
		$RM $LOG
	fi
}

print_results()
{
	for file in $OUT_DIR/$1/*.txt; do
		printf $CYAN'%-37s' " • $(basename -- $file .txt)$RESET"
		if [ -f $OUT_DIR/$2/${file##*/} ]; then
			echo -ne "Compiled: ✅  |  "
			diff <(sed '$d' $file) <(sed '$d' $OUT_DIR/$2/${file##*/}) > diff
			if [ -s diff ]; then
				echo -ne "Output: ❌"
			else
				echo -ne "Output: ✅  |  "
				FTTIME=$(tail -n 1 $OUT_DIR/$2/${file##*/}| sed 's/[^0-9\.]*//g') #truncate everything from time value except digits and decimals
				STDTIME=$(tail -n 1 $file| sed 's/[^0-9\.]*//g')
				echo -ne "FT Time:$GREEN" $FTTIME ms"$RESET |  "
				echo -ne "STD Time:$GREEN" $STDTIME ms"$RESET |  "
				STDTIME=$(expr $STDTIME*20 | bc)
				if [ $(bc <<< "$STDTIME < $FTTIME") -eq 1 ] #FT can be upto 20 times slower than the STD container
					then
						echo -ne "Time Compare: 🔴"
					else
						echo -ne "Time Compare: 🟢"
				fi
			fi
			rm diff
		else
			printf "Compiled: ❌  |  Output: ❌ "
		fi
		echo #new line
	done
	echo -e $BLUE"Checks outputs directory for results"$RESET
	check_compilation_status
}

run_tests() 
{
	for file in $OUT_DIR/$1/*.o; do
		$CC $CFLAGS $file -o ${file%%.o} # compile object files then run
		./${file%%.o} > ${file%%.o}.txt #redirect o/p to text file
		rm $file ${file%%.o} # delete object and executable file
	done
}

start_tests() 
{
	echo -e $YELLOW"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo -e "                                                          $3 Tester                                                      "
	echo -e "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"$RESET
	run_tests $1 
	run_tests $2 
	print_results $2 $1
}


#execution starts here with checking of the arguments
if [ "$#" -eq 0 ]; then
	echo -e $YELLOW"Please provide a valid container name (stack / vector / map / all)"$RESET
	exit 1

elif [ $1 == "stack" ]; then
	make clean && make -k stack 2> $LOG
	start_tests $FT_STACK $STD_STACK "stack"

elif [ $1 == "vector" ]; then
	make clean && make -k vector 2> $LOG
	start_tests $FT_VEC $STD_VEC "vector"


elif [ $1 == "map" ]; then
	make clean && make -k map 2> $LOG
	start_tests $FT_MAP $STD_MAP "map"

elif [ $1 == "all" ]; then
	make clean && make -k stack
	start_tests $FT_STACK $STD_STACK "stack"
	make -k vector
	start_tests $FT_VEC $STD_VEC "vector"
	make -k map
	start_tests $FT_MAP $STD_MAP "map"

else
	echo -e $YELLOW"Please enter a valid container name (stack / vector / map / all)"$RESET
	exit 1
fi