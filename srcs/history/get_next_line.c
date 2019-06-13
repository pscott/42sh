#include "ftsh.h"

static char		*ft_strjoinfree(char **s1, char *s2)
{
	char	*s3;

	if (!s2)
		return (0);
	if (!*s1)
		return (ft_strdup(s2));
	if (!(s3 = ft_strnew(ft_strlen(*s1) + ft_strlen(s2))))
		clean_exit(1, 1);
	if (s3)
	{
		ft_strcpy(s3, *s1);
		ft_strcat(s3, s2);
	}
	free(*s1);
	return (s3);
}

static int		check_content_value(char **content)
{
	if (!*content)
		return (1);
	if (**content == 0)
	{
		ft_strdel(content);
		return (1);
	}
	return (0);
}

static void		dup_line(char **line, char **content)
{
	if (!(*line = ft_strdup(*content)))
		clean_exit(1, 1);
	**content = 0;
}

static int		return_val(char **line, char **content)
{
	char			*next_nl;
	char			*tmp;

	tmp = NULL;
	if (check_content_value(content))
		return (0);
	next_nl = ft_strchr(*content, '\n');
	if (next_nl != NULL)
	{
		*next_nl = 0;
		if (!(*line = ft_strdup(*content)))
			clean_exit(1, 1);
		if (!(tmp = ft_strdup(next_nl + 1)))
			clean_exit(1, 1);
		ft_strdel(content);
		*content = tmp;
		return (1);
	}
	if (ft_strlen(*content) > 0)
	{
		dup_line(line, content);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*content = NULL;
	char			buf[1024];
	int				check;

	if (line == NULL || fd < 0)
		return (-1);
	*line = 0;
	if (!content)
	{
		if (!(content = ft_strdup("")))
			clean_exit(1, 1);
	}
	while ((check = read(fd, buf, 1023)) > 0)
	{
		buf[check] = 0;
		content = ft_strjoinfree(&content, buf);
	}
	if (check < 0)
	{
		ft_strdel(&content);
		return (-1);
	}
	return (return_val(line, &content));
}
