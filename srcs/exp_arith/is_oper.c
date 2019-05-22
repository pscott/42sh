#include "42sh.h"
#include "exp_arith.h"

/*
**	Identifying operators (and not iterators, which are deleted after
**	tokenization), and returning the size of them
*/

int		is_oper(char *str)
{
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2)
			|| !ft_strncmp(str, "!=", 2) || !ft_strncmp(str, "==", 2)
			|| !ft_strncmp(str, ">=", 2) || !ft_strncmp(str, "<=", 2))
		return (2);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1)
			|| !ft_strncmp(str, "%", 1) || !ft_strncmp(str, "/", 1)
			|| !ft_strncmp(str, "*", 1) || !ft_strncmp(str, "-", 1)
			|| !ft_strncmp(str, "+", 1) || !ft_strncmp(str, "%", 1))
		return (1);
	return (0);
}
