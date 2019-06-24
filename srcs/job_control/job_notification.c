#include "jobs.h"

static const char	*sig_str_2(int signal)
{
	if (signal == SIGSEGV)
		return ("Segmentation fault: 11");
	else if (signal == SIGSYS)
		return ("Bad system call: 12");
	else if (signal == SIGPIPE)
		return ("Broken pipe: 13");
	else if (signal == SIGALRM)
		return ("Alarm clock: 14");
	else if (signal == SIGTERM)
		return ("Terminated: 15");
	else if (signal == SIGXCPU)
		return ("Cputime limit exceeded: 24");
	else if (signal == SIGXFSZ)
		return ("Filesize limit exceeded: 25");
	else if (signal == SIGVTALRM)
		return ("Virtual timer expired: 26");
	else if (signal == SIGPROF)
		return ("Profiling timer expired: 27");
	else if (signal == SIGUSR1)
		return ("User defined signal 1: 30");
	else if (signal == SIGUSR2)
		return ("User defined signal 2: 31");
	return ("Running");
}

const char	*get_signal_str(int signal)
{
	if (signal == SIGHUP)
		return ("Hangup: 1");
	else if (signal == SIGINT)
		return ("Interrupt: 2");
	else if (signal == SIGQUIT)
		return ("Quit: 3");
	else if (signal == SIGILL)
		return ("Illegal instruction: 4");
	else if (signal == SIGTRAP)
		return ("Trace/BPT trap: 5");
	else if (signal == SIGABRT)
		return ("Abort trap: 6");
	else if (signal == SIGEMT)
		return ("EMT trap: 7");
	else if (signal == SIGFPE)
		return ("Floating point exception: 8");
	else if (signal == SIGKILL)
		return ("Killed: 9");
	else if (signal == SIGBUS)
		return ("Bus error: 10");
	else
		return (sig_str_2(signal));
}

const char	*get_stop_str(int sig)
{
	if (sig == SIGTTOU)
		return("Stopped (SIGTTOU)");
	else if (sig == SIGTSTP)
		return("Stopped (SIGTSTP)");
	else if (sig == SIGSTOP)
		return("Stopped (SIGSTOP)");
	else if (sig == SIGTTIN)
		return("Stopped (SIGTTIN)");
	return ("Stopped");
}

static char	*get_exit_str(int status)
{
	char	*msg;
	char	*itoa;

	if (WIFSIGNALED(status))
	{
		if (!(msg = ft_strdup(get_signal_str(WTERMSIG(status)))))
			clean_exit(1, 1);
	}
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

/*
**	Prints the job status.
**	Returns 1 if the job should be free'd. Else returns 0.
*/

int		print_job_status(t_job *j, int verbose, t_job_opt opt)
{
	char	*msg;
	int		sig;

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
	{
		sig = last_process_status(j->first_process);
		format_job_info(j, get_stop_str(WSTOPSIG(sig)), "", opt);
		j->fg = 0;
		j->notified = 1;
	}
	else if (verbose && !j->fg)
		format_job_info(j, "Running", "&", opt);
	return (0);
}

void		do_job_notification(int verbose, t_job_opt opt)
{
	t_job		*j;

	if (!g_isatty)
		return ;
	set_current();
	update_status();
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
