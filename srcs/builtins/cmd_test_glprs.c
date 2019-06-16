#include "builtins.h"
#include <sys/stat.h>

int		test_flag_g(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !(buf.st_mode & S_ISGID);
	return (0);
}

int		test_flag_cap_l(char *path, int *result)
{
	struct stat		buf;

	if (lstat(path, &buf) == -1)
		return (2);
	*result = !(S_ISLNK(buf.st_mode));
	return (0);
}

int		test_flag_p(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !((buf.st_mode & S_IFMT) == S_IFIFO);
	return (0);
}

int		test_flag_r(char *path, int *result)
{
	if (access(path, R_OK) == 0)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int		test_flag_cap_s(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !((buf.st_mode & S_IFMT) == S_IFSOCK);
	return (0);
}
