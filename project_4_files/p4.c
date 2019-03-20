#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char const *argv[]) {
  alarm(60);
//if(argc < 2){exit(0);}
//if(strcmp(argv[1], "-hw") == 0) { printf("%s\n","Hello world" ); exit(0); }
printf("I am %d\n",getpid() );
pid_t pid = fork();
printf("fork returned %d\n", (int)pid );

// child process
if(pid == 0)
{
  printf("I am the child with pid %d\n", (int)getpid() );
  // execute some code and exit
  exit(0);
}
// parent process
else if(pid > 0)
{
  printf("I am the parent waiting for child with pid %d\n", (int)getpid() );
  int status = 0;
  pid_t childPid = wait(&status);
  printf("parent knows child %d finished with status %d\n", (int)childPid, status  );
}



  return 0;
}
