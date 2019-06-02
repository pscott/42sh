#include "ftsh.h"
#include "exp_arith.h"

int		free_tokens(t_tok *tokens, int ret)
{
	int i;

	i = 0;
	while (tokens[i].token != 0)
	{
		if (tokens[i].varname)
			free(tokens[i].varname);
		i++;
	}
	free(tokens);
	return (ret);
}
