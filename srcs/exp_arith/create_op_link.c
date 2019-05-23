#include "42sh.h"
#include "exp_arith.h"

static	t_op	*init_link(int token, long long value, t_token link, t_op *new)
{
	new->prev = NULL;
	new->right = NULL;
	new->left = NULL;
	new->token = token;
	new->value = value;
	if (token == TK_NB)
	{
		if (link.varid == -2)
		{
			new->beg = 0;
			new->end = 0;
		}
		else
		{
			new->beg = link.beg;
			new->end = link.end;
		}
		new->varid = link.varid;
	}
	new->parent = 0;
	return (new);
}

t_op			*create_op_link(int token, long long value, t_token link)
{
	t_op	*new;

	if (!(new = (t_op*)malloc(sizeof(t_op))))
		ERROR_MEM;
	if (link.varname)
	{
		if (!(new->varname = ft_strdup(link.varname)))
			ERROR_MEM;
	}
	else
		new->varname = NULL;
	new = init_link(token, value, link, new);
	return (new);
}