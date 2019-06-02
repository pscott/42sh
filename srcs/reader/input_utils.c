#include "input.h"
#include "ftsh.h"

size_t	ft_printable_len(const char *s1)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s1 && s1[i])
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
	while (s1 && s1[i])
	{
		if (ft_isprint(s1[i]) || s1[i] == '\n')
		{
			res[len] = s1[i];
			len++;
		}
		i++;
	}
	res[len] = 0;
	return (res);
}

void	insert_str(t_st_cmd *st_cmd, const char *buf,
		size_t print_len) // remove print_len
{
	char		*printable_buf;
	t_st_txt	*st_txt;
	char		*end_line;

	st_txt = st_cmd->st_txt;
	if (!(printable_buf = ft_strdup_print(buf)))
		ERROR_MEM;
	print_len = ft_strlen(printable_buf);
	if (!(end_line = ft_strdup(&st_txt->txt[st_txt->tracker])))
		ERROR_MEM;
	ft_strcpy(&st_txt->txt[st_txt->tracker + print_len], end_line);
	ft_strdel(&end_line);
	ft_strncpy(&st_txt->txt[st_txt->tracker], printable_buf, print_len);
	free(printable_buf);
}
