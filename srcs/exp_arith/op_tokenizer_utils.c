#include "ftsh.h"
#include "exp_arith.h"

int			get_nb_len(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

void		clean_done_token(char *str, int len)
{
	int k;

	k = 0;
	while (str[k] && len > 0)
	{
		str[k] = ' ';
		len--;
		k++;
	}
}

int			get_tok_len(t_tok *tok)
{
	int i;

	i = 0;
	while (tok[i].token != 0)
		i++;
	return (i);
}

int			is_var(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	if (str[i] == '$')
		i++;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

int			check_next_tok(t_tok *dirty, int i)
{
	while (dirty[i].token != 0 && (dirty[i].token == tk_add
				|| dirty[i].token == tk_sub))
		i++;
	return (dirty[i].token);
}
