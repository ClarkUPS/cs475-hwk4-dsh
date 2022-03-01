/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"

//Definitions
#define HISTORY_LEN 100


// TODO: Your function definitions (declarations in dsh.h)

//History Globals:
char * history[HISTORY_LEN];
int hLoc = 0; //current locaion in array 
int gt100 = 0; //more than 100 elements


//Builtins!
 
 int checkbul(char * input){
    char firstWord[MAXBUF];
    char inputcpy[MAXBUF];
    strcpy(inputcpy,input);
    strcpy(firstWord, strtok(inputcpy, " ")); //just grab the first word. Also shrinks down the input by a word! (for addtional inputs)
   
    //Main function for bulitins FIX uses tests as input
	cmd_t isBuiltIn = chkBuiltin(firstWord);
	if(isBuiltIn ==  CMD_EXIT){
		printf("\nStudents all over the nation think your MOTD is inspiring!\n");
		return 1;
	}else if(isBuiltIn == CMD_CD){//DONE
        
        char newPath[MAXBUF]; //store new path!
        strcpy(newPath,getcwd(newPath,MAXBUF)); //give new path right off the bat
        
        char *token = strtok(input, " ");
        token = strtok(NULL, " ");//remove the first term
        strcat(newPath,"/");//add the nessasary "/""
        
        int justhome = 0;
        while(token != NULL){
            strcat(newPath,token);
            token = strtok(NULL, " ");
            justhome = 1;
        }
        if(justhome == 0){
            chdir(getenv("HOME"));
        }else{
            //test if access is possible:
        int sucsess = chdir(newPath);

        if(sucsess == 0){
            char newPWD[MAXBUF];
            strcpy(newPWD,getcwd(newPWD,MAXBUF));
            printf("\nNew PWD: %s",newPWD);
            }else{
                printf("\nERROR, sorry not valid path!");
            }
        }
    
        return 0;

    }else if(isBuiltIn == CMD_PWD){ //DONE
        
        char currentCWD[MAXBUF];
        getcwd(currentCWD,MAXBUF);
        printf("\nCWD: %s",currentCWD);
        return 0;

    }else if(isBuiltIn == CMD_HIST){ //History
        
        printf("\n***INPUT HISTORY***");
        int i;
        if(gt100 == 1){
        
        int rollOver = hLoc+1;
        for(i = 0; i < HISTORY_LEN; i++){
            printf("\nHistory: %s", history[i]);
            rollOver++;
            if(rollOver > HISTORY_LEN){
                rollOver = 0;
            }
        }
        }else{
        
        for(i = 0; i < hLoc; i++){
             printf("\n%s", history[i]);
        }
    }
        printf("\n***END OF HISTORY***\n");
    
        return 0;
    }else if(isBuiltIn == CMD_ECHO){
        printf("OP 5: ECHO: NOT IMPLEMENTED");
        return 0;
    }else{
        printf("NOT BUILTIN- RETURN BACK MAKE SURE WE MOVE ON!");
        return 2; //return 2 and move on
    } 

}


//Processing full path

void fullPath(char * input){
        //Create args list
        //char *args[3];
        //args[]; //Need the Args here
        //start
		printf("\nabsolute path!\n"); //REMOVE

		if(access(input, F_OK | X_OK) == 0){
			
			pid_t process;//process id
			process = fork(); //Fork the process no need to await here //pid_t

				if (process == 0){ //only run for the child process
					//execv(,); //wipe out the childs address space and runs the command line arg
					//need to get all the args figured out and sorted
				}
                    //if & run and do not wait!
                if(input[strlen(input)]-1 != '&'){
                   wait(NULL); 
                }
                

		}else{
			printf("\nERROR: Sorry bad absolute path\n");	//this ends here, jump back to dsh prompt!
		}
}


void addToHist(char * input){
    history[hLoc] = input;
    hLoc++;
    if(hLoc > HISTORY_LEN){
        gt100 = 1; //trigger bit
        hLoc = 0;
    }
}


    

//TO FINISH
//storing cd/changing it
//running execution path
//exec stuff