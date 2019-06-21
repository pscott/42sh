#include "builtins.h"
#include <sys/stat.h>

int		test_flag_b(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFBLK));
}

int		test_flag_c(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFCHR));
}

int		test_flag_d(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFDIR));
}

int		test_flag_e(char *path)
{
	if (access(path, F_OK) == 0)
		return (0);
	return (1);
}

int		test_flag_f(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFREG));
}
