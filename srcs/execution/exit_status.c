#include "signals.h"

int		exit_status(int status)
{
	int	ret;

	ret = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGPIPE)
			ft_dprintf(2, "process terminated, received signal : %d\n",
			WTERMSIG(status));
	}
	return (ret);
}
