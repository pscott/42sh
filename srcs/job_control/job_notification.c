#include "jobs.h"

static void	notify_stopped_job(t_job *j, t_job_opt opt)
{
	int		sig;

	sig = last_process_status(j->first_process);
	format_job_info(j, get_stop_str(WSTOPSIG(sig)), "", opt);
	j->fg = 0;
	j->bg = 0;
	j->notified = 1;
}

/*
**	Prints the job status.
**	Returns 1 if the job should be free'd. Else returns 0.
*/

int			print_job_status(t_job *j, int verbose, t_job_opt opt)
{
	char	*msg;

	if (!j)
		return (0);
	if (job_is_completed(j))
	{
		if (!j->fg)
		{
			msg = get_exit_str(last_process_status(j->first_process));
			format_job_info(j, msg, "", opt);
			ft_strdel(&msg);
		}
		return (1);
	}
	else if ((job_is_stopped(j) && !j->notified))
		notify_stopped_job(j, opt);
	else if (verbose && !j->fg)
		format_job_info(j, "Running", "&", opt);
	return (0);
}

void		do_job_notification(int verbose, t_job_opt opt)
{
	t_job		*j;

	if (!g_isatty)
		return ;
	update_status();
	set_current();
	if (!(j = g_first_job))
		return ;
	while (j)
	{
		if (print_job_status(j, verbose, opt))
			j = free_job_from_list(j);
		else
			j = j->next;
	}
}
