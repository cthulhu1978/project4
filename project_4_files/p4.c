#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
const int READ = 0;
const int WRITE = 1;

int main(int argc, char *argv[]) {
  alarm(60);
  if(argc < 2){exit(0);}
  if(strcmp(argv[1], "-hw") == 0) { printf("%s\n","Hello world" ); exit(0); }
  int sortPipe[2];
  pipe(sortPipe);
  pid_t pid = fork();

//////////// CHILD PROCESS ?????????????????????????????????
  if(pid == 0)
  {
    dup2(sortPipe[READ], STDIN_FILENO);
    close(sortPipe[WRITE]);
    close(sortPipe[READ]);
    // execute some code and exit
    char * args[] = {"/usr/bin/sort", NULL };
    execve(args[0], args, NULL);
  }

  //////////////// PARENT PROCESS /////////////////
  // unused by parent
  close(sortPipe[READ]);

  if(argc > 1){
    char * fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
      // TODO  check for foobar in each line. then pass to sort
      dprintf(sortPipe[1],"%s \n" , line);
    }
  }

  close(sortPipe[WRITE]);
  int status;
  pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting
  return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;

  return 0;
}
