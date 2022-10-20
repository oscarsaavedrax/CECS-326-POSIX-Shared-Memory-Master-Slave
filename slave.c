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
    const char *shared_mem_name = argv[1];
    const int SIZE = sizeof(struct SHARED_MEM_CLASS);

    struct SHARED_MEM_CLASS *shared_mem_struct;
    int shared_mem_fd;

    printf("Slave begins execution\n");
    printf("I am child number %s, received shared memory name %s\n", argv[0], argv[1]);

    shared_mem_fd = shm_open(shared_mem_name, O_RDWR, 0666);
    if(shared_mem_fd == -1)
    {
        printf("\nSlave %s: Shared memory failed: %s\n", argv[0], strerror(errno));
        exit(1);
    }
    else
    {
        // Map the shared memory segment
        shared_mem_struct = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED,
                                    shared_mem_fd, 0);
        if(shared_mem_struct == MAP_FAILED)
        {
        printf("\nSlave %s: Map failed: %s\n", argv[0], strerror(errno));
            /* close and shm_unlink */
            exit(1);
        }
        else
        {
            printf("SHARED MEM OPENED\n");
        }
        
        // Unmap the shared memory structure
        if(munmap(shared_mem_struct, SIZE) == -1)
        {
        printf("\nSlave %s: Unmap failed: %s\n", argv[0], strerror(errno));
            exit(1);
        }

        // Close the shared memory segment
        if (close(shared_mem_fd) == -1) 
        {
        printf("\nSlave %s: Close failed: %s\n", argv[0], strerror(errno));
            exit(1);
        }
    }

    return 0;
}