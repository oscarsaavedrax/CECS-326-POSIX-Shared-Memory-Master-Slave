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