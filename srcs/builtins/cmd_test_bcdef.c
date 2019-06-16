#include "builtins.h"
#include <sys/stat.h>

int		test_flag_b(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !((buf.st_mode & S_IFMT) == S_IFBLK);
	return (0);
}

int		test_flag_c(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !((buf.st_mode & S_IFMT) == S_IFCHR);
	return (0);
}

int		test_flag_d(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !((buf.st_mode & S_IFMT) == S_IFDIR);
	return (0);
}

int		test_flag_e(char *path, int *result)
{
	if (access(path, F_OK) == 0)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int		test_flag_f(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !((buf.st_mode & S_IFMT) == S_IFREG);
	return (0);
}
