#include "lexer.h"
#include "signals.h"
#include "execution.h"

/*
**	Returns the next simple_command (the one after the next pipe), if there
**	is one.
**	Should not return NULL because it is called n - 1 times
*/

static t_token	*get_next_simple_command(t_token *begin)
{
	while (is_simple_cmd_token(begin))
		begin = begin->next;
	if (begin && begin->type == tk_pipe)
		return (begin->next);
	else
	{
		ft_dprintf(2, "Error ???\n");
		return (begin); //error ?
	}
}

static	int		error_message(const char *cause)
{
	ft_dprintf(2, "%s error\n", cause);
	return (1);
}

/*
**	OUTDATED
**	Manages all pipes and fds, while handing the simple command to parse_redir
**	for redirection parsing and execution. Note that i < n - 1, because piping
**	the last command is never needed.
*/

static	int		fork_pipes(int num_simple_commands, t_token *beg, t_vars *vars)
{
	int		i;
	int		in;
	pid_t	pid;
	int		status;
	int		fd[2];
	int		ret;

	in = STDIN_FILENO;
	i = 0;
	ret = 0;
	while (i++ < num_simple_commands - 1)
	{
		if (pipe(fd))
			return (error_message("pipe"));
		if ((pid = fork()) == -1)
			return (error_message("fork"));
		else if (pid == 0)
		{
			close(fd[0]);
			clean_exit(parse_and_exec(beg, in, fd[1], vars), 0);
		}
		else if (pid > 0)
		{
			close(fd[1]);
			if (in != STDIN_FILENO)
				close(in);
			in = fd[0];
			beg = get_next_simple_command(beg);
			continue ;
		}
	}
	//break func here: fork_last_cmd() //TODO
	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "fork error\n");
		clean_exit(-1, 0);
	}
	else if (pid == 0)
		clean_exit(parse_and_exec(beg, in, STDOUT_FILENO, vars), 0);
	else
	{
		waitpid(pid, &status, 0);
		ret = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGPIPE)
				ft_dprintf(2, "process terminated, received signal : %d\n",
						WTERMSIG(status));
		}
		if (num_simple_commands != 1)
			close(fd[0]);
		while ((pid = wait(&status)) > 0)
			;
		signals_setup();
		setup_terminal_settings();
	}
	return (ret);
}

/*
** First counts the number of pipes and checks for correct pipe syntax
** then hands the token list to fork_pipes to handle pipes.
*/

int				parse_cmdline(t_token *token, t_vars *vars)
{
	int		num_simple_commands;
	t_token *probe;
	int		ret;

	if (!token)
		return (0);
	num_simple_commands = 1;
	probe = token;
	while (probe)
	{
		while (probe && is_simple_cmd_token(probe))
			probe = probe->next;
		if (probe && probe->next && (probe->type == tk_pipe))
		{
			probe = probe->next;
			num_simple_commands++;
		}
	}
	if ((num_simple_commands == 1)
			&& (ret = execute_no_pipe_builtin(token, vars)) >= 0)
		return (ret);
	ret = fork_pipes(num_simple_commands, token, vars);
	return (ret);
}
