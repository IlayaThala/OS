#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(void)
{
int shmid;
char *shmPtr;
int n;
if (fork( ) == 0)
{
sleep(5); /* UUPS */
if( (shmid = shmget(2041, 32, 0)) == -1 )
{

exit(1);
}
shmPtr = shmat(shmid, 0, 0);
if (shmPtr == (char *) -1)
exit(2);
printf ("\nChild Reading ....\n\n");
for (n = 0; n < 26; n++)
putchar(shmPtr[n]);
putchar('\n'); }
else
{
if( (shmid = shmget(2041, 32, 0666 | IPC_CREAT)) == -1 )
{
exit(1);
}
shmPtr = shmat(shmid, 0, 0);
if (shmPtr == (char *) -1)
exit(2);
for (n = 0; n < 26; n++)
shmPtr[n] = 'a' + n;
printf ("Parent Writing ....\n\n") ;
for (n = 0; n < 26; n++)
putchar(shmPtr[n]);
putchar('\n'); wait(NULL);
shmdt(NULL);
if( shmctl(shmid, IPC_RMID, NULL) == -1 )
{
printf("shmctl");
exit(-1);
}
}
exit(0);
}
