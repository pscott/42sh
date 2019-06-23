#include "jobs.h"

int		case_bg(char **argv)
{
	t_job	*to_print;
	int		i;

	(void)argv;//
	update_status();
	if (!argv[1])
		to_print = get_job("%+", "bg");
	else
	{
		i = 1;
		while (argv[i])
		{
			to_print = get_job(argv[i], "bg");
			if (print_job_status(to_print, 1))
				free_job_from_list(to_print);
			i++;
		}
	}
	if (job_is_completed(to_print))
	{
		ft_dprintf(2, SHELL_NAME ": bg: job has terminated\n");
		return (1);
	}
	if (put_job_in_background(to_print, 1))
		return (1);
	ft_dprintf(STDERR_FILENO, "[%d]%c %s&\n",
			to_print->num, to_print->current, to_print->command);
	return (0);
}
