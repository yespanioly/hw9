#!/bin/bash
shopt -s xpg_echo
touch results.txt
total_packets=$(cat /dev/stdin)
#remove clutter
while read -r packet
do
	packet=$(echo "${packet}" | sed 's/ //g' | awk -F# '{print $1}')
	packet=$(echo "${packet}" | sed -E 's/,+/,/g')
	if [[ "${packet::1}" == ',' ]]; then
		packet=$(echo "$packet" | sed 's/,//')
	fi
	if [[ "$packet" != "" ]]; then
		echo "$total_packets" > curr_packets.txt
		IFS=',' read -r -a rule_arr <<< "$packet"
		for rule in "${rule_arr[@]}"
		do
			./firewall.exe "$rule" < curr_packets.txt > tmp_packets.txt
			cat tmp_packets.txt > curr_packets.txt
		done
		cat curr_packets.txt >> results.txt
	fi
done<$1 #done
#sort results
cat results.txt | sort -u | sed 's/ //g'
rm curr_packets.txt results.txt tmp_packets.txt
