#include "ftsh.h"
#include "exp_arith.h"

int		c_number(t_tok *d, t_tok **c, t_integ *v)
{
	(*c)[(*v).k].token = tk_nb;
	(*c)[(*v).k].varid = d[(*v).i].varid;
	if (d[(*v).i].varid == -2)
		(*c)[(*v).k].value = d[(*v).i].value * (*v).moins;
	else
	{
		(*c)[(*v).k].value = (*v).moins;
		if (!((*c)[(*v).k].varname = ft_strdup(d[(*v).i].varname)))
			clean_exit(1, 1);
	}
	(*v).moins = 1;
	(*v).prev = 'n';
	(*v).k++;
	return (0);
}

void	c_operator(t_tok *d, t_tok **c, t_integ *v)
{
	if (check_put_oper(v->prev, d, v->i))
		insert_clean_token(d, c, v);
	else if (d[v->i].token == tk_sub)
		invert_value(&v->moins);
}
