#include "input.h"
#include "ftsh.h"
#include "line_editing.h"

size_t		ft_printable_len(const char *s1)
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

static void	ft_strcpy_print(char *dest, const char *source)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (source && source[i])
	{
		if (ft_isprint(source[i]) || source[i] == '\n')
		{
			dest[len] = source[i];
			len++;
		}
		i++;
	}
	dest[len] = 0;
}

char		*ft_strdup_print(const char *s1)
{
	char	*res;

	if (!(res = ft_strnew(ft_printable_len(s1))))
		return (NULL);
	ft_strcpy_print(res, s1);
	return (res);
}

static char	*ft_strndup_print(const char *s1, size_t print_len)
{
	char *res;

	if (!(res = ft_strnew(print_len)))
		return (NULL);
	ft_strcpy_print(res, s1);
	return (res);
}

void		insert_str(t_st_cmd *st_cmd, const char *buf,
	size_t print_len)
{
	t_st_txt	*st_txt;
	char		*print_buf;
	char		*end_line;

	st_txt = st_cmd->st_txt;
	if (!(print_buf = ft_strndup_print(buf, print_len)))
		clean_exit(1, 1);
	if (!(end_line = ft_strdup(&st_txt->txt[st_txt->tracker])))
		clean_exit(1, 1);
	ft_strcpy(&st_txt->txt[st_txt->tracker + print_len], end_line);
	ft_strdel(&end_line);
	ft_strncpy(&st_txt->txt[st_txt->tracker], print_buf, print_len);
	ft_strdel(&print_buf);
}
