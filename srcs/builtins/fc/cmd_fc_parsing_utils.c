#include "ftsh.h"
#include "history.h"
#include "auto_completion.h"

int			is_valid_option(char c)
{
	if (!ft_strchr("selnr", c))
		return (0);
	return (1);
}

int			is_valid_mix(char flag[4], char c)
{
	if (ft_strchr(flag, c))
		return (0);
	if (c != 's' && ft_strchr(flag, 's'))
		return (-1);
	if (c == 'e' && (ft_strchr(flag, 'l') || ft_strchr(flag, 'n')))
		return (-1);
	if (c == 's' && flag[0] != '.')
		return (-1);
	if (c == 'e' && (ft_strchr(flag, 'l') || ft_strchr(flag, 'n')
				|| ft_strchr(flag, 's')))
		return (-1);
	if (c == 'l' && ft_strchr(flag, 'e'))
		return (-1);
	return (1);
}
