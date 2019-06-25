#include "builtins.h"
#include "env.h"
#include "errors.h"
#include "execution.h"
#include "signals.h"

char		*join_with_space(const char *s1, const char *s2)
{
	char	*res;
	char	*tmp;

	if (!(res = ft_strjoin(s1, " ")))
		clean_exit(1, 1);
	tmp = res;
	if (!(res = ft_strjoin(res, s2)))
		clean_exit(1, 1);
	ft_strdel(&tmp);
	return (res);
}

int			exec_bin(char **argv)
{
	t_st_cmd	*tmp_cmd;
	t_vars		*vars;
	int			status;

	if (!argv[0] || !argv[1])
		return (-1);
	vars = get_vars(NULL);
	if (!vars)
		return (1);
	tmp_cmd = init_st_cmd((const char**)vars->env_vars); // care for history ?
	ft_strdel(&tmp_cmd->st_txt->txt);
	if (!(tmp_cmd->st_txt->txt = join_with_space(argv[0], argv[1])))
		clean_exit(1, 1);
	status = handle_input(tmp_cmd, vars);
	free_all_st_cmds(&tmp_cmd);
	return (status);
}
