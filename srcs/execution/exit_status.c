#include "signals.h"

int		exit_status(int status)
{
	int	ret;

	ft_dprintf(2, "status: %d\n", status);
	ret = WIFSTOPPED(status) ? WSTOPSIG(status) : 0;
	ft_dprintf(2, "STOPPED: %d\n", ret);
	ret = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
	return (ret);
}
