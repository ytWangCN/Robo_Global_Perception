#!/bin/bash
while :
do
	cd /home/robotlab
	status=` ps -ef | grep Radar | grep -v "grep" | wc -l `
	echo $status
    	if [ $status -eq 0 ];then
    		echo "starting"
    		cd /home/robotlab/Radar_2021/Loadings
        	sudo ./Radar
    	fi
    	sleep 0.01
done
    
