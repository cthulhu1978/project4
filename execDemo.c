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
  pid_t type = fork();
  if(type == 0){
    char * args[] = {"/bin/date", NULL };
    execve(args[0],args, NULL);
    //exit(0);
  } else if(type > 0){
    printf("parent process\n" );
  }
  wait(NULL);
  return 0;
}
