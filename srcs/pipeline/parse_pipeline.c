/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:02 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "signals.h"
#include "execution.h"
#include "cmd_parsing.h"

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
		return (begin);
}

/*
**	Executes the last cmd and wait for children to finish.
**	Returns the exit status of the last cmd executed and prints an error
**	message if the last cmd exited because of a signal.
**	Had to use an array of ints for ints because of 42's norme.
*/

static int		exec_last_cmd(t_token *begin, int ints[2], int fd[2],
	t_vars *vars)
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
		clean_exit(parse_and_exec(begin, ints[0], STDOUT_FILENO, vars), 0);
	else
	{
		waitpid(pid, &status, 0);
		ret = exit_status(status);
		if (ints[1] != 1)
			close(fd[0]);
		while ((pid = wait(&status)) > 0)
			;
		signals_setup();
		setup_terminal_settings();
	}
	return (ret);
}

/*
**	Pipes fd.
**	Creates a fork :if it's a child, parses and executes starting from the
**	begin token.
**	If it's a father, closes fd[1], and sets ints[0] to fd[0].
*/

static void		create_forks(t_token **begin, int ints[2], int fd[2],
	t_vars *vars)
{
	int	pid;

	if ((pid = fork()) == -1)
	{
		write(2, "fork error\n", 11);
		clean_exit(-1, 0);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		pid = parse_and_exec(*begin, ints[0], fd[1], vars);
		clean_exit(pid, 0);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		if (ints[0] != STDIN_FILENO)
			close(ints[0]);
		ints[0] = fd[0];
		*begin = get_next_simple_command(*begin);
	}
}

/*
**	Manages all pipes and fds, while handing the simple command to
**	parse_and_exec for redirection parsing and execution. Note that i < n - 1,
**	because piping the last command is never needed.
**
**	Declared variable ints[2] because of 42's norme.
**	ints[0] was a variable called in.
**	ints[1] was a variable called num_simple_commands.
*/

static	int		fork_pipes(int num_simple_commands, t_token *beg, t_vars *vars)
{
	int		i;
	int		ints[2];
	int		fd[2];
	int		ret;

	i = 0;
	ints[0] = STDIN_FILENO;
	ints[1] = num_simple_commands;
	reset_terminal_settings();
	while (i++ < num_simple_commands - 1)
	{
		if (pipe(fd))
		{
			write(2, "pipe error\n", 11);
			clean_exit(-1, 0);
		}
		create_forks(&beg, ints, fd, vars);
	}
	ret = exec_last_cmd(beg, ints, fd, vars);
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
		&& ((ret = check_no_pipe_builtin(token, vars)) >= 0 || ret == -2))
		return (ret);
	ret = fork_pipes(num_simple_commands, token, vars);
	return (ret);
}
