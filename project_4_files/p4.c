#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
/*
1) arg length and hello world
2) Pipe/Duplicate Logic
3) Create an array of args to pass to execve
4) Fork process into parent and child process
*/



int main(int argc, char *argv[]) {
  // Mandatory alarm
  alarm(60);

  //(1) Check arg length and print Hello world if neccessary //
  //if(argc < 2){exit(0);}
  //if(strcmp(argv[1], "-hw") == 0) { printf("%s\n","Hello world" ); exit(0); }

  //(2) Create Duplicate/PIPE Logic // 0 = stdin, 1 = stdout;
  char * buff[255];
  int std_in[2], std_out[2];

  //(3) create array of args to pass to execve
  char * argsToPass[argc];
  for (size_t i = 0; i < argc; i++) { argsToPass[i] = argv[i]; }

  //
  printf("I am %d\n",getpid() );
  pid_t pid = fork();
  printf("fork returned %d\n", (int)pid );

  // child process
  if(pid == 0)
  {
    printf("I am the child with pid %d\n", (int)getpid() );
    // execute some code and exit
    // execve(bin/sort + args)
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
