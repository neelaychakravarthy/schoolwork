# Name: Neelay Chakravarthy
# Date: 4/5/2023
# Title: Lab1 - task 2
# Description: This program computes the radius and circumference of a circle given a radius from the user

#!/bin/sh

radius=0
A=0
C=0
area(){
	A=`echo "$radius * $radius * 3.14" | bc`
}

perimeter(){
	C=`echo "2 * $radius * 3.14" | bc`
}

response="Yes"
while [ $response != "No" ]
do
	echo "Enter radius of circle: "
	read radius
	if [ $radius -gt 0 ]
	then
		area
		echo "The area of the circle is $A"
		perimeter
		echo "The perimeter of the circle is $C"
	else
		echo "Invalid radius"
	fi
	echo "Would you like to repeat for another circle? [Yes/No]?"
	read response
done
