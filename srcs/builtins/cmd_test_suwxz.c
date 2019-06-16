#include "builtins.h"
#include <sys/stat.h>

int		test_flag_s(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !(buf.st_size > 0);
	return (0);
}

int		test_flag_u(char *path, int *result)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (2);
	*result = !(buf.st_mode & S_ISUID);
	return (0);
}

int		test_flag_w(char *path, int *result)
{
	if (access(path, W_OK) == 0)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int		test_flag_x(char *path, int *result)
{
	if (access(path, X_OK) == 0)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int		test_flag_z(char *path, int *result)
{
	if (!path[0])
		*result = 0;
	else
		*result = 1;
	return (0);
}
