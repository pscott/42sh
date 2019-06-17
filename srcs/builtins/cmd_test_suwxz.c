#include "builtins.h"
#include <sys/stat.h>

int		test_flag_s(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!(buf.st_size > 0));
}

int		test_flag_u(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!(buf.st_mode & S_ISUID));
}

int		test_flag_w(char *path)
{
	if (access(path, W_OK) == 0)
		return (0);
	return (1);
}

int		test_flag_x(char *path)
{
	if (access(path, X_OK) == 0)
		return (0);
	return (1);
}

int		test_flag_z(char *path)
{
	if (path && !path[0])
		return (0);
	return (1);
}
