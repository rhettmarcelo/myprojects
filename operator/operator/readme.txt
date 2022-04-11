April 10, 2022

A program that contains a function of type string that takes three integer parameters and returns the mathematical operators used by the first and second parameters which results the third parameter. 

Sample input1: 1,2,3 returns "+"
Sample input2: 2,2,4 returns "+*"
Sample input3: 1,2,-1 returns "-"
Sample input4: 3,3,1 returs "/"
Sample input5: 10,11,12 returns "None"

The program was improved by:
	-adding failproofs, such as user input will continue to loop until user inputs a valid value of type int (i.e. string and char inputs are invalid when asking numbers, thus it will loop)
	-looping until the user wishes to exit
