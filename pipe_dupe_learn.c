#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
const int READ = 0;
const int WRITE = 1;

int main(int argc, char **argv) {

  int i, rc;
  // create pipe file descriptors;
  int std[2];//, std_out[2];
  char Buffer[100];
  // create a pipe for each process
  pipe(std);
  //pipe(std_out);

  // Now fork the process :
  rc = fork();
  if(rc == 0){
    printf("child %d\n",getpid() );
    close(std[WRITE]);
    dup(std[READ]);
    int j = read(std[0], Buffer, 100);
    char * const envp[] = { NULL };

    char * const args[] = {"/bin/ls", "-l",  "-a" };
    execve(args[0], args, envp);

    //printf("buffer -> %s\n",Buffer );
  }

  if(rc > 0){
    printf("parent process\n" );
    close(std[READ]);
    dup(std[WRITE]);
    //sleep(2);
    i = write(std[1],"hello\n",7);
    wait(NULL);
  }

  return 0;
}
