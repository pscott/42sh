#include "42sh.h"
#include "exp_arith.h"

int		c_number(t_tok *d, t_tok **c, t_integ *v)
{
	(*c)[(*v).k].token = TK_NB;
	(*c)[(*v).k].varid = d[(*v).i].varid;
	if (d[(*v).i].varid == -2)
		(*c)[(*v).k].value = d[(*v).i].value * (*v).moins;
	else
	{
		(*c)[(*v).k].value = (*v).moins;
		if (!((*c)[(*v).k].varname = ft_strdup(d[(*v).i].varname)))
			ERROR_MEM;
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
	else if (d[v->i].token == TK_SUB)
		invert_value(&v->moins);
}
