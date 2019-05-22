#include "42sh.h"
#include "exp_arith.h"

/*
**	Arithmetic expansion errors
*/

static	int		err_msgs(int err)
{
	if (err == 1)
		ft_printf("Syntax error : unauthorized character\n");
	else if (err == 2)
		ft_printf("Error malloc\n");
	else if (err == 3)
		ft_printf("Syntax error : several numbers in a row\n");
	else if (err == 4)
		ft_printf("Error : division by 0\n");
	else if (err == 5)
		ft_printf("Syntax error : number missing\n");
	return (err);
}

/*
**	Arithmetic expansion : takes a string, returns the status of the arithmetic
**	expansion, and gives the result in the 'result' argument is no err happened
*/

int				expansion_arith(char *str, char ***vars, long long *result)
{
	int		ret;
	t_op	*lst;
	t_token	*tokens;
	int		k;

	k = 0;
	if (ft_str_isempty(str))
		return (0);
	if (check_chars(str))
		return (err_msgs(1));
	if (op_tokenizer(str, &tokens, vars))
		return (err_msgs(2));
	lst = build_op_list(tokens);
	ret = exec_op_list(lst, vars, result);
	free_tokens(tokens, 0);
	free_lst(lst, 0);
	return (err_msgs(ret));
}
