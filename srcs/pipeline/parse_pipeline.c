#include "lexer.h"
#include "signals.h"
#include "execution.h"

/*
**	Returns the next simple_command (the one after the next pipe), if there
**	is one.
**	Should not return NULL because it is called n - 1 times
*/

static t_token *get_next_simple_command(t_token *begin)
{
	while (is_simple_cmd_token(begin))
		begin = begin->next;
	if (begin && begin->type == tk_pipe)
		return (begin->next);
	else
	{
		ft_dprintf(2, "Error ???\n"); // 
		return (begin); //error ?
	}
}

static void	Close(int fd) //remove me pls
{
	if (close(fd) < 0)
	{
		ft_dprintf(2, "FAILED TO CLOSE :%d", fd);
		print_line(2);
	}
}

/*	OUTDATED
**	Manages all pipes and fds, while handing the simple command to parse_redir
**	for redirection parsing and execution. Note that i < n - 1, because piping \
**	the last command is never needed.
*/

static int	fork_pipes(int num_simple_commands, t_token *begin, t_vars *vars)
{
	int i; // num_simple_commands - 1 can decrement
	int in;
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int fd[2];

	in = STDIN_FILENO;
	i = 0;
	if (num_simple_commands == 1)
		if (execute_only_one_cmd(begin, vars) == 0)
			return (0);
	while (i < num_simple_commands - 1)
	{
		if (pipe(fd))
		{
			ft_dprintf(2, "pipe error\n"); //dprintf //exit ?
			return (0);
		}
		if ((pid = fork()) == -1)
			ft_dprintf(2, "fork error\n");//TODO dprintf //exit ?
		else if (pid == 0)
		{
			Close(fd[0]);//check return value
			execute_in_fork(begin, in, fd[1], vars);
			clean_exit(1);
		}
		else if (pid > 0)
		{
			Close(fd[1]); //protect
			if (in != STDIN_FILENO)
				Close(in); // check if it's a proper way of doing things
			in = fd[0];
			i++;
			begin = get_next_simple_command(begin);
		}
	}
	status = 0; //necessary ?
	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "fork error\n"); //exit ?
		return (0);
	}
	else if (pid == 0)
	{
		execute_in_fork(begin, in, STDOUT_FILENO, vars);
		clean_exit(1);
		return (0);
	}
	else
	{
		if (num_simple_commands != 1)
			Close(fd[0]);
		while ((wpid = wait(&status)) > 0) //not sure if it's proper
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGPIPE)
				{
					ft_dprintf(2, "process terminated, received signal : %d", WTERMSIG(status));
					print_line(2);
				}
			}
		}
		signal_setup();
		//Close(STDIN_FILENO); // for fd leaks
		if (setup_terminal_settings() == 0)
			clean_exit(1); // ? 
		return (WEXITSTATUS(status));
	}
}

/*
** First counts the number of pipes and checks for correct pipe syntax
** then hands the token list to fork_pipes to handle pipes.
*/

int			parse_pipeline(t_token *token, t_vars *vars) // no need for t_pipelst ?
{
	int	num_simple_commands;
	t_token *probe;

	if (!token)
		return (0);
	num_simple_commands = 1;
	probe = token;
	while (probe)
	{
		while (probe && is_simple_cmd_token(probe)) //continue on simple_cmd tokens
			probe = probe->next;
		if (probe && probe->next && (probe->type == tk_pipe)) // is a pipe and not empty after
		{
			probe = probe->next;
			num_simple_commands++;
		}
	}
	return (fork_pipes(num_simple_commands, token, vars));
}
