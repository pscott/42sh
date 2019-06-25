#include "jobs.h"
#include "signals.h"

int		case_fg(char **argv)
{
	t_job	*j;
	int		ret;

	if (!g_isatty)
		return (0);
	update_status();
	if (!argv[1])
		j = get_job("%+", "fg");
	else
		j = get_job(argv[1], "fg");
	if (!j)
		return (1);
	if (job_is_completed(j))
	{
		ft_dprintf(2, SHELL_NAME ": fg: job has terminated\n");
		return (1);
	}
	ft_dprintf(2, "%s\n", j->command);
	reset_terminal_settings();
	if (job_is_stopped(j))
		ret = put_job_in_foreground(j, 1);
	else
		ret = put_job_in_foreground(j, 0);
	setup_terminal_settings();
	return (ret);
}
