#include "ftsh.h"
#include "exp_arith.h"
#include "env.h"

/*
**	Arithmetic expansion errors
*/

static	int		err_msgs(int err, int verbose)
{
	if (verbose)
	{
		if (err == 2)
			ft_dprintf(STDERR_FILENO, "%s: error malloc\n", SHELL_NAME);
		else if (err == 3)
			ft_dprintf(STDERR_FILENO,
				"%s: syntax error : several numbers in a row\n",
				SHELL_NAME);
		else if (err == 4)
			ft_dprintf(STDERR_FILENO, "%s: error : division by 0\n",
				SHELL_NAME);
		else if (err == 5)
			ft_dprintf(STDERR_FILENO, "%s: syntax error : number missing\n",
				SHELL_NAME);
	}
	return (err);
}

/*
**	Arithmetic expansion : takes a string, returns the status of the arithmetic
**	expansion, and gives the result in the 'result' argument is no err happened
*/

int				expansion_arith(char *str, long long *result, t_vars *vars)
{
	int		ret;
	t_op	*lst;
	t_tok	*tokens;

	if (ft_str_isempty(str))
		return (0);
	if (check_chars(str, vars))
		return (err_msgs(1, vars->verbose));
	if (op_tokenizer(str, &tokens, &vars->shell_vars))
		return (err_msgs(2, vars->verbose));
	lst = build_op_list(tokens);
	ret = exec_op_list(lst, vars, result);
	free_tokens(tokens, 0);
	free_lst(lst, 0);
	return (err_msgs(ret, vars->verbose));
}
