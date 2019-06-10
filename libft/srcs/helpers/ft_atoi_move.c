#include "ft_printf.h"

int		ft_atoi_move(char **str)
{
	int		finalnb;

	finalnb = 0;
	while (ft_isdigit(**str))
	{
		finalnb = finalnb * 10 + **str - '0';
		(*str)++;
	}
	return (finalnb);
}
