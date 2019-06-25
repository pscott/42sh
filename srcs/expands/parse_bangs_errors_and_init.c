#include "cmd_parsing.h"
#include "errors.h"

int				is_quoted(char *str, int i)
{
	int			k;
	int			quote;

	k = 0;
	quote = -1;
	while (k < i && str[k])
	{
		if (str[k] == '\"')
			quote *= -1;
		k++;
	}
	return (quote);
}

int				error_bang(char **str, int *i, int mode)
{
	if (mode)
		return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR,
				&((*str)[(*i) - 1])));
	else
		return (1);
}

int				int_vars_bang(t_st_cmd *st_cmd, int *i, int *ret)
{
	*i = -1;
	st_cmd = get_st_cmd(NULL);
	*ret = 0;
	if (st_cmd->is_cr_sqt == 1)
		return (1);
	return (0);
}

int				bang_max(int *count)
{
	write(2, "Too many history expansions.\n", 29);
	count = 0;
	return (1);
}
