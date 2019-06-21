#include "ftsh.h"
#include "exp_arith.h"

char	*get_value_index(int i, char **env)
{
	if (env && env[i])
		return (ft_strrchr(env[i], '=') + 1);
	return (NULL);
}
