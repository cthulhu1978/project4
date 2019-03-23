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
    //printf("args listed out %d\n",argc );

    // create array, set first element, add additional options, add Null at end
    //char * args[argc + 1];
    // args[0] = "/usr/bin/sort";
    // for (size_t i = 1; i <= argc; i++) { args[i] = argv[i]; }
    // args[argc+1] = NULL;

    char * args[] = {"/usr/bin/sort", "-r", NULL };
    execve(args[0], args, NULL);
  }

  //////////////// PARENT PROCESS /////////////////
  if(pid > 0){
  // unused by parent
    close(sortPipe[READ]);
    char * fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    char line[256];

    const char * word = "foobar";
    while (fgets(line, sizeof(line), file)) {
        char * ret = (strstr(line, word));
        if(ret == NULL){
        dprintf(sortPipe[1],"%s \n" , line);
        }
    }

    close(sortPipe[WRITE]);
    int status;
    pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting
    return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}
  return 0;
}
