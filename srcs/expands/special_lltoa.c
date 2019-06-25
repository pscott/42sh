#include "cmd_parsing.h"
#include "exp_arith.h"

static size_t	get_ll_len(long long nb)
{
	size_t	len;

	len = (nb < 0) ? 1 : 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char		*check_min(long long nb)
{
	char *str;

	if ((unsigned long long)nb == -9223372036854775808U)
	{
		if (!(str = ft_strdup("-9223372036854775808")))
			clean_exit(1, 1);
		return (str);
	}
	return (NULL);
}

char			*lltoa_and_free(long long nb, char **to_free)
{
	char		*str;
	int			len;

	ft_strdel(to_free);
	if ((str = check_min(nb)))
		return (str);
	len = get_ll_len(nb);
	if (!(str = ft_strnew(len)))
		clean_exit(1, 1);
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		str[len-- - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
