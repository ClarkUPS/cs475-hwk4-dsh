/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h> //for white space detection
#include "dsh.h"
#include "builtins.h"

int main(int argc, char **argv)
{
	char cmdline[MAXBUF]; // stores user input from commmand line

	//Try and print the message of the day:

	char * motd = (char*)malloc(MAXBUF * sizeof(char));
	strcpy(motd,getenv("HOME")); //use strcpy here as it won't work if you concatinate useing strcat on an empty string
	strcat(motd, "/"); //concatinate the empty new array with the
	strcat(motd,"/.dsh_motd"); //concatinate the location of the file
	
	printf("PRINT OUT: %s \n", motd); //REMOVE Test to see if the location is correcet

		if (access(motd, F_OK ) == 0){
			
			FILE * mesFile;
			mesFile = fopen(motd, "r");//open the file
			
			if(mesFile == NULL){
				printf("\nSorry, input could not be found (MOTD)");
			}else{
				char MOTD[MAXBUF];
					//	fgets(MOTD, MAXBUF, mesFile);
				while(fgets(MOTD, MAXBUF, mesFile)){ //this runs will run and remember that the 
					printf("%s", MOTD); //print the message
				}
			}
			
			fclose(mesFile); //close the file
		
		}else{
			printf("\nSorry, input could not be found (MOTD)");//REMOVE
		}

	//End of message of the day


	//START OF SHELL LOOP!/////////////////////////////////////////////////////////////////////////////////////////
	int builtinExit = 0; 
	while(builtinExit == 0){ //loop until the built in exit turns to 1 when "exit" is entered
	
			//Get input for command line
		printf("\ndsh>");
		fgets(cmdline,MAXBUF,stdin);
		cmdline[strlen(cmdline)-1] = '\0'; //need to remove the final charter before passing it on!

			//Add to history array
			//printf("\nADD TO HIST CMDLN: %s\n",cmdline); TOTO FIX HISTORY
			addToHist(cmdline);

			//make sure the first charter is not white space!
		if(!isspace(cmdline[0])){
			printf("\nNo white space good to go!\n");
			
			if(cmdline[0] == '/'){
				//Absolute path
				fullPath(cmdline);
			}else{
				builtinExit = checkbul(cmdline);//run buitins on input test against!
				
				if(builtinExit == 2){//check for constructed path
					
				}
			}
			
		}else{
			printf("\nERROR: please do not lead an input with white space\n");
		}
	}

	//temporary input
	// printf("\nCMDLN: %s\n",cmdline);
	// int option = checkbul(cmdline);
	// printf("Option: %d\n",option);
	
	
	
	//absolute path!
	
	//malloc array of char * to what end

	// /bin/ls

	//path concatinate
	

	
	




	


	return 0;
}



//QUESTIONS

//get the dsh> command line//

//Meaning of "F_OK | X_OK" from access command

//Builtins

