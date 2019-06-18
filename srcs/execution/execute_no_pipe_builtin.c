#include "builtins.h"
#include "execution.h"
#include "cmd_parsing.h"
#include "hashmap.h"
#include "env.h"

/*
**	Utility function to actually exit
*/

static void		execute_exit(int exitno)
{
	print_exit();
	save_close_openfds(0, 0);
	save_reset_stdfd(0);
	clean_exit(exitno, 0);
}

/*
**	Parses expands, redirections, and executes builtin on the real token_list.
**	Returns 0 on success : else returns error number
*/

static int		no_pipe_builtin(t_token *token_head, t_vars *vars, int cmd_id)
{
	char	**argv;
	int		ret;
	//char	**env_cpy;
	char	**env_save;
	int		have_assign;

	have_assign = 0;
	if ((ret = parse_expands(token_head, vars)) != 0)
		return (ret);
	if ((ret = parse_redirections(token_head, 1) > 0))
	{
		save_close_openfds(0, 0);
		save_reset_stdfd(0);
		return (ret);
	}
	if ((have_assign = parse_assignation(token_head, vars)))//if ret = 1, make an env cpy
	{
		//save and make a cpy
		env_save = get_ntab_cpy(vars->env_vars);
		apply_assignation_to_ntab(vars->assign_tab, &vars->env_vars);
	}
	argv = NULL;
	get_argv_from_token_lst(token_head, &argv);
	ret = exec_builtins(argv, vars, cmd_id);
	//restore old env
	if (have_assign)
	{
		ft_free_ntab(vars->env_vars);
		vars->env_vars = env_save;
	}
	//
	if (cmd_id == cmd_exit)
	{
		if (ret == 1)
			execute_exit(vars->cmd_value);
		else
			ret = vars->cmd_value;
	}
	save_close_openfds(0, 0);
	save_reset_stdfd(0);
	return (ret);
}

/*
**	Returns a freshly allocated `fake` argv, because redirections have not
**	been applied.
*/

static char		**fake_argv(t_token *token_head, t_vars *vars)
{
	t_token					*cpy;
	char					**argv;

	argv = NULL;
	vars->verbose = 0;
	cpy = copy_tokens(token_head);
	parse_expands(cpy, vars);
	parse_redirections(cpy, -1);
	parse_assignation(cpy, vars);
	get_argv_from_token_lst(cpy, &argv);
	free_token_list(cpy);
	vars->verbose = 1;
	return (argv);
}

/*
**	Creates a temporary argv and checks if argv[0] is a builtin.
**	If argv[0] contains a '/'.
**	If argv[0] is a builtin.
**	If argv[0] is in hashmap, adds a hit tag to it, but does not execute.
**	If argv[0] is not in hashmap, add it to hashmap and add a hit to it but
**	does not execute it.
**	If argv[0] is a builtin:
**			- if it got executed, returns 0.
**			- if there was an error returns error number
**	Else (argv[0] is NOT a builtin) returns -1.
**	If execution should stop, returns -2
*/

int				check_no_pipe_builtin(t_token *token_head, t_vars *vars)
{
	char					**argv;
	unsigned int			cmd_id;
	int						ret;
	char					*cmd_path;

	if (!(argv = fake_argv(token_head, vars)) || !argv[0])
	{
		ft_printf("EMPTY ARGV\n");//so add to shell_vars
		//apply_assignation(vars->assign_tab, &vars->shell_vars);
		apply_assignation(vars->assign_tab, vars);
		return (-1);
	}
	//else add to env
	//test (BAD cause it should set env just for the given cmd)
	if (ft_strchr(argv[0], '/'))
		ret = -1;
	else if ((cmd_id = check_builtins(argv)))
		ret = no_pipe_builtin(token_head, vars, cmd_id);
	else if ((cmd_path = check_hashmap(argv[0], vars->hashmap, hash_exec)))
		ret = -1;
	else
	{
		if ((cmd_path = get_cmd_path(argv[0], vars->env_vars, 0)))
		{
			add_to_hashmap(argv[0], cmd_path, &vars->hashmap);
			check_hashmap(argv[0], vars->hashmap, hash_exec);
			ft_strdel(&cmd_path);
		}
		ret = -1;
	}
	ft_free_ntab(argv);
	return (ret);
}
