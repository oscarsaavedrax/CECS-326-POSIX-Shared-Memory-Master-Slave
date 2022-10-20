/***********************************************************************
 * Programmer	: Oscar Saavedra
 * Class	    : CECS 326-01
 * Due Date	    : October 18, 2022
 * Description	: This program makes use of the POSIX implementation of
 *  the Linux shared memory mechanism. This master.c program takes in a 
 *  name for the shared memory segment and the number of children to
 *  make. The program requests to create a shared memory segment. The
 *  program creates n children and passes each one the name of the shared
 *  memory segment and the child number. The program then waits for all
 *  children to execute. Once all children execute, the program outputs
 *  the content of the shared memory, removes the shared memory, and
 *  exits.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    // Display identification
    printf("Master begins execution\n");

    // Create shared memory segment
    printf("Master created a shared memory segment named %s\n", argv[2]);

    // Create n children
    printf("Master created %s child processes to execute slave\n\n", argv[1]);
    for(int i = 0; i < atoi(argv[1]); i++)
    {
        // Fork a new child on each iteration
        if(fork() == 0)
        {
            // Convert child integer to char
            char child_num[20];
            sprintf(child_num, "%d", i+1);

            // Create array with child information
            char* child_info[] = {child_num, argv[2], NULL};

            // Child process will execute slave program
            execv("./slave", child_info);
            exit(0);
        }
    }

    // Wait for children to finish to terminate
    for(int i = 0; i < atoi(argv[1]); i++)
        wait(NULL);
    printf("\nMaster waits for all child processes to terminate\n");
    printf("Master received termination signals from all %s child processes\n", argv[1]);

    return 0;
}