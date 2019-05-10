#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0) //child
	{
		exit(1);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
//	close(fd[1]);
//	close(fd[0]);
	write(STDOUT_FILENO, "salut", 5);
	return (1);
}
