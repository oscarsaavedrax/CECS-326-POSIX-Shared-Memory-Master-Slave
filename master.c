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

#include "myShm.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char** argv)
{
    // Create variables
    struct SHARED_MEM_CLASS shm_structure;
    int shared_mem_fd;

    // Display identification
    printf("Master begins execution\n");

    // Create shared memory segment
    shared_mem_fd = shm_open(argv[2], O_CREAT | O_RDWR, 0666);
    if(shared_mem_fd == -1)
    {
        printf("\nMaster: Shared memory failed: %s\n", strerror(errno));
        exit(1);
    }
    else
    {
        printf("Master created a shared memory segment named %s\n", argv[2]);
    }
    
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


    // Close the shared memory segment
    if (close(shared_mem_fd) == -1) {
      printf("prod: Close failed: %s\n", strerror(errno));
      exit(1);
    }

    // Delete the shared memory segment
    shm_unlink(argv[2]);
    return 0;
}