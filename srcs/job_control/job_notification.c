#include "jobs.h"

static char	*get_signal_str(int sig)
{
	char	*msg;
	char	*itoa;

	if (sig == SIGTTOU)
		return(ft_strdup("Stopped (SIGTTOU)"));
	else if (sig == SIGTSTP)
		return(ft_strdup("Stopped (SIGTSTP)"));
	else if (sig == SIGSTOP)
		return(ft_strdup("Stopped (SIGSTOP)"));
	else if (sig == SIGTTIN)
		return(ft_strdup("Stopped (SIGTTIN)"));
	if (!(itoa = ft_itoa(sig)))
		clean_exit(1, 1);
	if (!(msg = ft_strjoin("Received signal: ", itoa)))
		clean_exit(1, 1);
	ft_strdel(&itoa);
	return (msg);
}

static char	*get_exit_str(int status)
{
	char	*msg;
	char	*itoa;

	if (WIFSIGNALED(status))
		msg = get_signal_str(status);
	else
	{
		if (WEXITSTATUS(status) == 0)
			return (ft_strdup("Done"));
		if (!(itoa = ft_itoa(WEXITSTATUS(status))))
			clean_exit(1, 1);
		if (!(msg = ft_strjoin("Done(", itoa)))
			clean_exit(1, 1);
		if (!(msg = ft_strjoin_free_left(msg, ")")))
			clean_exit(1, 1);
		ft_strdel(&itoa);
	}
	return (msg);
}

void		do_job_notification(int verbose)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;
	char		*msg;

	set_current();
	update_status();
	jlast = NULL;
	j = g_first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
		{
			if (j->notified == 0 && !j->fg)
			{
				msg = get_exit_str(j->status);
				format_job_info(j, msg, "");
				ft_strdel(&msg);
			}
			if (jlast)
				jlast->next = jnext;
			else
				g_first_job = jnext;
			free_job(j);
		}
		else if ((job_is_stopped(j) && !j->notified))
		{
			format_job_info(j, "Stopped", ""); // need to change for sigttou etc
			j->notified = 1;
			jlast = j;
		}
		else
		{
			if (verbose && !j->fg)
				format_job_info(j, "Running", "&");
			jlast = j;
		}
		j = jnext;
	}
}
