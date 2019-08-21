#include "libft.h"

static int	get_num_len(int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

static void	fill_itoa(int n, char *src, int len)
{
	while (n > 9)
	{
		src[len - 1] = n % 10 + '0';
		len--;
		n = n / 10;
	}
	src[0] = n + '0';
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_num_len(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		fill_itoa(-n, &res[1], len - 1);
	}
	else
		fill_itoa(n, res, len);
	return (res);
}
