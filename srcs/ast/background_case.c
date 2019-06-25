#include "jobs.h"
#include "cmd_parsing.h"

static void	and_or_child(t_job *j, t_ast *root, t_vars *vars, pid_t pid)
{
	int	ret;

	close(TERM_FD);
	pid = getpid();
	j->pgid = pid;
	setpgid(pid, j->pgid);
	ret = exec_ast(root, vars, 0);
	free_job_list(g_first_job);
	exit(ret);
}

static void	execute_and_or_background(t_job *j, t_ast *root, t_vars *vars)
{
	pid_t	pid;

	j->forked = 1;
	if ((pid = fork()) < 0)
	{
		write(2, "fork error\n", 11);
		clean_exit(1, FORCE);
	}
	else if (pid == 0)
		and_or_child(j, root, vars, pid);
	if (g_isatty)
	{
		j->first_process = create_process(NULL);
		j->first_process->pid = pid;
		j->pgid = pid;
		setpgid(pid, j->pgid);
		if (!(j->first_process->process_str = ft_strdup(j->command)))
			clean_exit(1, 1);
		ft_dprintf(STDERR_FILENO, "[%d] %d\n", j->num, j->pgid);
	}
}

static int	background_exec(t_ast *root, t_vars *vars)
{
	t_job	*j;

	if (!root)
		return (0);
	j = append_job(&g_first_job, create_job(root, 0,
				get_last_num(g_first_job) + 1));
	if (root->token->type >= tk_and)
		execute_and_or_background(j, root, vars);
	else
		return (parse_cmdline(root, vars, 0));
	return (0);
}

int			background_case(t_ast *root, t_vars *vars, int fg)
{
	if (!root || !root->left)
		return (1);
	if (root->left->token->type == tk_amp)
		background_case(root->left, vars, 0);
	else
		background_exec(root->left, vars);
	if (fg)
		exec_ast(root->right, vars, 1);
	else
		background_exec(root->right, vars);
	return (0);
}
