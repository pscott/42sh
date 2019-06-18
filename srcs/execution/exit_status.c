#include "signals.h"

int		exit_status(int status)
{
	int	ret;

	ret = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
	return (ret);
}
