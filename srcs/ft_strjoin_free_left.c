#include "ftsh.h"

/*
**	Joins two strings and frees the one given by the first parameter.
*/

char			*ft_strjoin_free_left(char *s1, const char *s2)
{
	char			*res;
	unsigned int	s1_len;

	if (!s2 && !s1)
		return (NULL);
	if (!s1 && (!s2[0]))
		return (ft_strdup(s2));
	if (!s2 && (!s1[0]))
	{
		res = ft_strdup(s1);
		ft_strdel(&s1);
		return (res);
	}
	s1_len = ft_strlen(s1);
	if (!(res = ft_strnew(s1_len + ft_strlen(s2))))
		clean_exit(1, 1);
	ft_strcpy(res, s1);
	ft_strcat(&res[s1_len], s2);
	ft_strdel(&s1);
	return (res);
}
