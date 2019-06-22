#include "builtins.h"
#include <sys/stat.h>

int		test_flag_g(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!(buf.st_mode & S_ISGID));
}

int		test_flag_cap_l(char *path)
{
	struct stat		buf;

	if (lstat(path, &buf) == -1)
		return (1);
	return (!(S_ISLNK(buf.st_mode)));
}

int		test_flag_p(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFIFO));
}

int		test_flag_r(char *path)
{
	if (access(path, R_OK) == 0)
		return (0);
	return (1);
}

int		test_flag_cap_s(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFSOCK));
}
