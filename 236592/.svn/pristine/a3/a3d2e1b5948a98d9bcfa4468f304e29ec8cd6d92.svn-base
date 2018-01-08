#!/bin/bash

max_line=50

#declare -i sectors_read_old;
#declare -i sectors_read_new;
reads=([0]=0 [1]=0 [2]=0 [3]=0 [4]=0)

#declare -i sectors_write_old;
#declare -i sectors_write_new;
writes=([0]=0 [1]=0 [2]=0 [3]=0 [4]=0)

#declare -i avg
avgs=([0]=0 [1]=0 [2]=0 [3]=0 [4]=0)


sectors_read_old=$(awk '/sda /{print $8}' /proc/diskstats)

tput sc

show(){
var=$1
prefix_numb=1
prefix_name="B"

if [[ $var -ge 1024 ]]; then
	var=$(($var/1024))
	prefix_numb=$(($prefix_numb*1024))
	prefix_name="KB"
	if [[ $var -ge 1024 ]]; then
		var=$(($var/1024))
		prefix_numb=$(($prefix_numb*1024))
		prefix_name="MB"
		if [[ $var -ge 1024 ]]; then
			var=$(($var/1024))
			prefix_numb=$(($prefix_numb*1024))
			prefix_name="GB"
		fi
	fi
fi
   echo -e -n "$var $prefix_name\t"  
}


while true; do


	for((i=0; i<21;i++)); do
		echo
	done
	for((i=0; i<21;i++)); do
		tput cuu1
	done

	tput sc
	sectors_read_new=$(awk '/sda /{print $6}' /proc/diskstats)

	max=1
	for((i=(${#reads[@]} - 1); i > 0; i--)); do
		reads[$i]=${reads[$i - 1]}
		if [[ $max -lt ${reads[$i]} ]]
		then max=${reads[$i]}
		fi
	done

	reads[0]=$(((sectors_read_new - sectors_read_old) * 512)) 
	sectors_read_old=$sectors_read_new
	
	if [[ $max -lt ${reads[0]} ]]
	then max=${reads[0]}
	fi

	max_in_B=$max
	prefix_numb=1
	prefix_name="B"
	if [[ $max -ge 1024 ]]; then
		max=$(($max/1024))
		prefix_numb=$(($prefix_numb*1024))
		prefix_name="KB"
		if [[ $max -ge 1024 ]]; then
			max=$(($max/1024))
			prefix_numb=$(($prefix_numb*1024))
			prefix_name="MB"
			if [[ $max -ge 1024 ]]; then
				max=$(($max/1024))
				prefix_numb=$(($prefix_numb*1024))
				prefix_name="GB"
			fi
		fi
	fi
			
	tput el
	echo
	tput el
	echo "Odczyt:"
	for read in "${reads[@]}"; do
		tput el
		show "$read"
		for((j=0; j < ($read*$max_line/$max_in_B); j++)); do
			echo -n "#"
		done
		echo
	done	
	
	sectors_write_new=$(awk '/sda /{print $8}' /proc/diskstats)

	max=1
	for((i=(${#writes[@]} - 1); i > 0; i--)); do
		writes[$i]=${writes[$i - 1]}
		if [[ $max -lt ${writes[$i]} ]]
		then max=${writes[$i]}
		fi
	done

	writes[0]=$(((sectors_write_new - sectors_write_old) * 512)) 
	sectors_write_old=$sectors_write_new
	
	if [[ $max -lt ${writes[0]} ]]
	then max=${writes[0]}
	fi

	max_in_B=$max
	prefix_numb=1
	prefix_name="B"
	if [[ $max -ge 1024 ]]; then
		max=$(($max/1024))
		prefix_numb=$(($prefix_numb*1024))
		prefix_name="KB"
		if [[ $max -ge 1024 ]]; then
			max=$(($max/1024))
			prefix_numb=$(($prefix_numb*1024))
			prefix_name="MB"
			if [[ $max -ge 1024 ]]; then
				max=$(($max/1024))
				prefix_numb=$(($prefix_numb*1024))
				prefix_name="GB"
			fi
		fi
	fi

	tput el
	echo		
	tput el
	echo "Zapis"
	for write in "${writes[@]}"; do
		tput el
		show "$write"
		for((j=0; j < ($write*$max_line/$max_in_B); j++)); do
			echo -n "#"
		done
		echo
	done	

	avg=$(awk '{print $1}' /proc/loadavg)
	avg="${avg##*.}"

	max=1
	for((i=(${#avgs[@]} - 1); i > 0; i--)); do
		avgs[$i]=${avgs[$i - 1]}
	done

	avgs[0]=$avg 
	
	tput el
	echo			
	tput el
	echo "Obciazenie systemu"
	for avg in "${avgs[@]}"; do
		tput el
		echo -e -n "$avg %:\t"
		for((j=0; j < ($avg*$max_line/100); j++)); do
			echo -n "#"
		done
		echo
	done	
	
	sleep 1
	
	tput rc
done
