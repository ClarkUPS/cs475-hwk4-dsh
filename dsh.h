/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define HISTORY_LEN 100

char * history[HISTORY_LEN]; //to store the history
int histcount; //for the position in the array(so it can loop)


// TODO: Your function prototypes below
int checkbul(char * input);

void fullPath(char * input); //try and run absolute path!
