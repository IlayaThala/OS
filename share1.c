// SERVER CODE



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSIZE 27
main()
{
char c;
int shmid;
key_t key;
char *shm, *s;
/* * We'll name our shared memory segment * "5678". */
key = 5678;
/* * create the segment.* */
if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
{
perror("shmget");
exit(1);
}
/** Now we attach the segment to our data space.*/
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
{
perror("shmat");
exit(1);
}
/** Now put some things into the memory for the other process to read. */

s = shm;
for (c = 'a'; c <= 'z'; c++)
*s++ = c;
*s = NULL;
/** Finally, we wait until the other process
* Changes the first character of our memory
* to '*', indicating that it has read what
* we put there.
*/
while (*shm != '*')
sleep(1);
exit(0);
}


// CLIENT CODE


/* shm_client.c */
/*
* shm-client - client program to demonstrate shared
memory. */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSIZE 27
main()
{
int shmid;
key_t key;
char *shm, *s;
/*
* We need to get the segment named
* "5678", created by the server.
*/
key = 5678;
/*
* Locate the
segment. */
if ((shmid = shmget(key, SHMSIZE, 0666)) < 0)
{ perror("shmget");
exit(1);
}
/*
* Now we attach the segment to our data
space. */
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
{ perror("shmat");
exit(1);
}
/*
* Now read what the server put in the
memory. */
for (s = shm; *s != NULL; s++)
putchar(*s);
putchar('\n');
/*
* Finally, change the first character of the
* segment to '*', indicating we have read
* the segment.
*/
*shm = '*';
printf ("\nIts done from client.\n\n\n");
exit(0);
}



// HOW TO RUN

gcc server_file_name.c -o server_file_name
gcc client_file_name.c -o client_file_name
./server_file_name &
./client_file_name
