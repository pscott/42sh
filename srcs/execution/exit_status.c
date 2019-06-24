#include "signals.h"

int		exit_status(int status)
{
	int	ret;

	if ((ret = WIFSTOPPED(status) ? 128 + WSTOPSIG(status) : 0))
		return (ret);
	ret = WIFSIGNALED(status) ? 128 + WTERMSIG(status) : WEXITSTATUS(status);
	return (ret);
}
