/***********************************************************************
 * Programmer	: Oscar Saavedra
 * Class	    : CECS 326-01
 * Due Date	    : October 18, 2022
 * Description	: This program makes use of the POSIX implementation of
 *  the Linux shared memory mechanism. This slave.c program receives its
 *  number and name of the shared memory segment via commandline
 *  arugments from master.c program. This program then outputs a message
 *  to identify itself. The program opens the existing shared memory 
 *  segment, acquires access to it, and write its child number into the
 *  next available slot in the shared memory. The pgrogram then closes
 *  the shared memory segment and terminates.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    printf("Slave begins execution\n");
    printf("I am child number %s, received shared memory name %s\n", argv[0], argv[1]);

    return 0;
}