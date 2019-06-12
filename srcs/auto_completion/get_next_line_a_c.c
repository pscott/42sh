/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_a_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:04 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:08 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

size_t			ft_strlen_eol(char *s)
{
	size_t			i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

static int		ft_fill_line(char **file, char **line, int fd)
{
	char			*tmp;
	char			*ptr;

	ptr = ft_strchr(file[fd], '\n');
	if (ptr)
	{
		*line = ft_strndup(file[fd], ft_strlen_eol(file[fd]));
		if (!(tmp = ft_strdup(++ptr)))
			return (-1);
		free(file[fd]);
		file[fd] = tmp;
		if (!(file[fd][0]))
			ft_strdel(&(file[fd]));
	}
	else
	{
		if (!(*line = ft_strdup(file[fd])))
			return (-1);
		ft_strdel(&file[fd]);
	}
	return (1);
}

int				get_next_line_a_c(const int fd, char **line)
{
	static char		*file[MAX_FD];
	char			buf[BUFF_SIZE + 1];
	char			*stock;
	int				ret;

	if (fd < 0 || fd > MAX_FD || read(fd, buf, 0) < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if (!(file[fd]))
			file[fd] = ft_strnew(1);
		if (!(stock = ft_strjoin(file[fd], buf)))
			return (-1);
		free(file[fd]);
		file[fd] = stock;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!(file[fd]) || ft_strlen(file[fd]) == 0)
		return (0);
	return (ft_fill_line(file, line, fd));
}
