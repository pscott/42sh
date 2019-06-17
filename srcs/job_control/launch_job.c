static int		exec_last_cmd(t_process *p, t_job *j, int fd[2], int in);
{
	int		status;
	pid_t	pid;
	int		ret;

	ret = 0;
	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "fork error\n");
		clean_exit(ret, 0);
	}
	else if (pid == 0)
		clean_exit(parse_and_exec(p->token_list, in, STDOUT_FILENO, vars), 0);
	else
	{
		waitpid(pid, &status, 0);
		ret = exit_status(status);
		while ((pid = wait(&status)) > 0)
			;
		signals_setup();
		execute_str(MOVE_DOWN);
		setup_terminal_settings();
	}
	return (ret);
}

static void		create_forks(t_process *p, t_job *j, int fd[2], int *in)
{
	int	pid;

	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "fork error\n");
		clean_exit(1, 0);
	}
	else if (pid == 0)
		clean_exit(parse_and_exec(p->token_list, in, fd[1]), 0);
	else if (pid > 0)
	{
		p->pid = pid;
		if (g_shell_is_interactive)
		{
			if (!j->pgid)
				j->pgid = pid;
			setpgid(pid, j->pgid);
		}
		*in = fd[0];
	}
}

int		launch_job(t_job *j, int foreground)
{
	t_process	*p;
	int			in;
	int			fd[2];
	int			ret;

	i = 0;
	in = STDIN_FILENO;
	p = j->first_process;
	reset_terminal_settings();
	while (p->next)
	{
		if (pipe(fd))
		{
			write(2, "pipe error\n", 11);
			clean_exit(1, 0);
		}
		create_forks(p, j, fd, &in);
	}
	ret = exec_last_cmd(p, j, fd, in);
	format_job_info (j, "launched");
	if (!g_shell_is_interactive)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
	return (ret); // missing signals
}
