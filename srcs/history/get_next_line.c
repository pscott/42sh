#include "get_next_line.h"

static char		*ft_strjoinfree(char *s1, char *s2)
{
	char	*s3;

	if (!s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	s3 = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (s3)
	{
		ft_strcpy(s3, s1);
		ft_strcat(s3, s2);
	}
	ft_strdel(&s1);
	return (s3);
}

static t_fdlist	*ft_dlistnew(int fd)
{
	t_fdlist *i;

	if (!(i = (t_fdlist*)malloc(sizeof(t_fdlist))))
		return (NULL);
	i->c = NULL;
	i->fd = fd;
	i->next = NULL;
	return (i);
}

static int		return_val(char **line, t_fdlist *save)
{
	char			*e;
	char			*tmp;

	if (!(save->c))
		return (0);
	e = ft_strchr(save->c, ENDL);
	if (e != NULL)
	{
		*e = 0;
		*line = ft_strdup(save->c);
		tmp = ft_strdup(e + 1);
		free(save->c);
		save->c = tmp;
		return (1);
	}
	if (ft_strlen(save->c) > 0)
	{
		*line = ft_strdup(save->c);
		*(save)->c = 0;
		return (1);
	}
	/* should be return create_new */
	return (0);
}

static t_fdlist	*getfd(t_fdlist *save, int fd)
{
	t_fdlist *dlist;

	while (save->fd < fd && save)
	{
		if (!save->next)
		{
			dlist = ft_dlistnew(fd);
			if (save != NULL && dlist != NULL)
			{
				save->next = dlist;
				dlist->prev = save;
			}
		}
		save = save->next;
		if (save->fd == fd)
			return (save);
	}
	while (save->fd > fd && save)
	{
		save = save->prev;
		if (save->fd == fd)
			return (save);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_fdlist	*save = NULL;
	char			*buf;
	int				check;

	if (line == NULL || GNL_BUFF_SIZE < 1 || fd < 0)
		return (-1);
	if (save && (int)save->fd != fd && fd)
		save = getfd(save, fd);
	if (save == NULL)
		save = ft_dlistnew(fd);
	*line = 0;
	if (!(buf = (char *)malloc(sizeof(char) * (GNL_BUFF_SIZE + 1))))
		return (-1);
	while ((check = read(fd, buf, GNL_BUFF_SIZE)) > 0)
	{
		buf[check] = 0;
		save->c = ft_strjoinfree(save->c, buf);
	}
	if (check < 0)
		return (-1);
	free(buf);
	return (return_val(line, save));
}
