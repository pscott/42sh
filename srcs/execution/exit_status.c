#include "signals.h"

int		exit_status(int status)
{
	int	ret;

	ret = WIFSTOPPED(status) ? WSTOPSIG(status) : 0;
	ret = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
	return (ret);
}
