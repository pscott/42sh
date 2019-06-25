#include "cmd_parsing.h"
#include "env.h"
#include "execution.h"
#include "builtins.h"

static int		clean_fds(int ret)
{
	save_close_openfds(0, 0);
	save_reset_stdfd(0);
	return (ret);
}

/*
**	Utility function to actually exit
*/

static void		execute_exit(int exitno)
{
	print_exit();
	clean_fds(0);
	clean_exit(exitno, EXIT);
}

static void		set_assign(t_token *token_head, t_vars *vars)
{
	static int	have_assign = 0;

	if (have_assign)
	{
		ft_memdel_ntab(&vars->env_vars);
		vars->env_vars = get_ntab_cpy(vars->env_save);
		ft_memdel_ntab(&vars->env_save);
		have_assign = 0;
	}
	else
	{
		if ((have_assign = parse_assignation(token_head, vars)))
		{
			vars->env_save = get_ntab_cpy(vars->env_vars);
			apply_assignation_to_ntab(&vars->assign_tab, &vars->env_vars);
		}
	}
}

/*
**	Parses expands, redirections, and executes builtin on the real token_list.
**	Returns 0 on success : else returns error number
**
**	if parse_assignation() find assignations:
**	- copy current env into env_cpy
**	- apply assignation to the cpy
**	- exec
**	- restore old env
*/

int		exec_no_pipe_builtin(t_token *token_head, t_vars *vars,
		t_cmd_id cmd_id)
{
	char	**argv;
	int		ret;

	if ((ret = parse_expands(token_head, vars)) != 0)
		return (ret);
	if ((ret = parse_redirections(token_head, 1) > 0))
		return (clean_fds(ret));
	set_assign(token_head, vars);
	argv = NULL;
	get_argv_from_token_lst(token_head, &argv);
	ret = exec_builtins(argv, vars, cmd_id);
	ft_free_ntab(argv);
	set_assign(token_head, vars);
	if (cmd_id == cmd_exit)
	{
		if (ret == 1)
			execute_exit(vars->cmd_value);
		else
			ret = vars->cmd_value;
	}
	else
		g_can_exit = 0;
	clean_fds(0);
	ft_memdel_ntab(&vars->env_save);
	return (ret ? 256 * ret : 0);
}
