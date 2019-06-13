#include "ftsh.h"
#include "exp_arith.h"

int		ft_str_isempty(const char *s)
{
	int i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (!ft_is_white_space(s[i]))
			return (0);
	}
	return (1);
}
