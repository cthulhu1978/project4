#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main(int argc, char **argv)
{
    int i, rc;
    int stdin_pipe_fds[2], stdout_pipe_fds[2], stderr_pipe_fds[2];
    char buf[100];
    
    pipe(stdin_pipe_fds);
    pipe(stdout_pipe_fds);
    pipe(stderr_pipe_fds);
    rc = fork();
    if (rc == -1)
    {
        printf("fork failed\n");
	exit(-1);
    }
    if (rc == 0)  /* child */
    {
        close(stdin_pipe_fds[1]);
        close(stdout_pipe_fds[0]);
        close(stderr_pipe_fds[0]);

        close(0);
	dup(stdin_pipe_fds[0]);
	close(stdin_pipe_fds[0]);
        close(1);
	dup(stdout_pipe_fds[1]);
	close(stdout_pipe_fds[1]);
        close(2);
	dup(stderr_pipe_fds[1]);
	close(stderr_pipe_fds[1]);

	/* provide invalid date; causing prt on stderr as well as stdout */
	rc = execlp("/bin/date", "/bin/date", "01010101", NULL);
	exit(0);
    }
    /* parent */
    close(stdin_pipe_fds[0]);
    close(stdout_pipe_fds[1]);
    close(stderr_pipe_fds[1]);
    /* The following write is commented out because this parent
       process may write to the pipe after the child has exited
       since this child program does no reading.
       In that case, it would get a SIGPIPE and be terminated.
       I have found that some shells are better than others at
       telling you what happened in those cases.
    */
    /* i = write(stdin_pipe_fds[1],"hello\n",7); */
    if ((i = read(stdout_pipe_fds[0],buf,100)) > 0)
    {
	buf[i] = '\0';
        printf("stdout: %s\n",buf);
    }
    if ((i = read(stderr_pipe_fds[0],buf,100)) > 0)
    {
	buf[i] = '\0';
        printf("stderr: %s\n",buf);
    }
}
