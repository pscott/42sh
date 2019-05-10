#include "reader.h"
#include "tosh.h"

size_t	ft_printable_len(const char *s1)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]) || s1[i] == '\n')
			res++;
		i++;
	}
	return (res);
}

char	*ft_strdup_print(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	if (!(res = ft_strnew(ft_printable_len(s1))))
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]) || s1[i] == '\n')
		{
			res[len] = s1[i];
			len++;
		}
		i++;
	}
	res[i] = 0;
	return (res);
}

void	insert_str(t_st_cmd *st_cmd, const char *buf,
		size_t printable_len)
{
	char		*tmp;
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	if (!(tmp = ft_strdup_print(&st_txt->txt[st_txt->tracker])))
		ERROR_MEM;
	ft_strcpy(&st_txt->txt[st_txt->tracker + printable_len],
			tmp);
	ft_strncpy(&st_txt->txt[st_txt->tracker], buf, printable_len);
	free(tmp);
}
