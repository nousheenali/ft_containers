#!/usr/bin/env bash

DEFAULT=$(tput sgr0)
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
PURPLE='\033[1;35m'
CYAN='\033[1;36m'
BLUE='\033[1;34m'

CC=c++
CFLAGS='-Wall -Wextra -Werror'
VALGRIND=valgrind
VFLAGS='--leak-check=full --show-leak-kinds=all'
RM='rm -rf'
LOG=compilation.log
TEST_DIR=output

STACK_DIR=stack_tests
STD_STACK=std_stack
FT_STACK=ft_stack

VEC_DIR=vector
STD_VEC=std_vector
FT_VEC=ft_vector

MAP_DIR=map_tests
STD_MAP=std_map
FT_MAP=ft_map

check_compilation_log_file() 
{
	if [ -s $LOG ]; then
		echo -e $RED"Compilation error, check $LOG for more details"$DEFAULT
	else
		$RM $LOG
	fi
}

print_test_results()
{
	for file in $TEST_DIR/$1/*.txt; do
		printf $PURPLE'%-37s' " • $(basename -- $file .txt)$DEFAULT"
		if [ -f $TEST_DIR/$2/${file##*/} ]; then
			echo -ne "Compiled:$GREEN SUCCESS $DEFAULT |  "
			diff <(sed '$d' $file) <(sed '$d' $TEST_DIR/$2/${file##*/}) > diff
			if [ -s diff ]; then
				echo -ne "Result:$RED FAILURE $DEFAULT"
			else
				echo -ne "Result:$GREEN SUCCESS $DEFAULT |  "
				echo -ne "FT Time:$GREEN" $(tail -n 1 $TEST_DIR/$2/${file##*/}) "$DEFAULT |  "
				echo -ne "STD Time:$GREEN" $(tail -n 1 $file)" $DEFAULT"
			fi
			rm diff
		else
			printf "Compiled:$RED FAILURE $DEFAULT |  Result:$RED FAILURE $DEFAULT"
		fi
		echo #new line
	done
	echo -e $BLUE"Checks outputs directory for results"$DEFAULT
	check_compilation_log_file
}

execute_and_redirect_output() 
{
	for file in $TEST_DIR/$1/*.o; do
		# compile object files then run and redirect output to a text file
		$CC $CFLAGS $file -o ${file%%.o}
		./${file%%.o} > ${file%%.o}.txt
		# delete object and executable file
		rm $file ${file%%.o}
	done
}

start_tests() 
{
	echo -e $YELLOW"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"$DEFAULT
	echo -e $YELLOW"                                                  $3 Tester                                                 "$DEFAULT
	echo -e $YELLOW"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"$DEFAULT
	execute_and_redirect_output $1 
	execute_and_redirect_output $2 
	print_test_results $2 $1
}


#execution starts here with checking of the arguments
if [ "$#" -eq 0 ]; then
	echo -e $YELLOW"Please provide a valid container name (stack / vector / map / all)"$DEFAULT
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
	make -k stack
	start_tests $FT_MAP $STD_MAP "map"

else
	echo -e $YELLOW"Please enter a valid container name (stack / vector / map / all)"$DEFAULT
	exit 1
fi
