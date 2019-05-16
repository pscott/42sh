#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int c;
	int fd;

	c = 4;
	fd = open("salut.txt", O_WRONLY | O_CREAT);
	write(fd, &c, 1);
	return (1);
}
