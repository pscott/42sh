/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:17 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:21 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "heredoc.h"

/*
** get_heredoc_finename
** concatenate the default heredoc_filename with the given key
** and returned it
*/

static char	*get_heredoc_filename(unsigned int file_key)
{
	char			*path;
	char			*file_key_str;

	if (!(path = ft_strnew(ft_strlen(HEREDOC_FILENAME) + MAX_INT_LEN)))
		clean_exit(1, 1);
	ft_strcpy(path, HEREDOC_FILENAME);
	if (!(file_key_str = ft_itoa((int)file_key)))
		clean_exit(1, 1);
	ft_strcpy(&path[ft_strlen(HEREDOC_FILENAME)], file_key_str);
	ft_memdel((void*)&file_key_str);
	return (path);
}

/*
** find_unique_filename
** find an unused filename
** and returned it
*/

static char	*find_uniq_filename(void)
{
	char			*path;
	unsigned int	file_key;

	file_key = 0;
	path = get_heredoc_filename(file_key);
	while (access(path, F_OK) == 0)
	{
		ft_strdel(&path);
		if (file_key == UINT_MAX)
		{
			ft_dprintf(2,
				"%s: can't create heredoc temporary file(max UINT)\n",
				SHELL_NAME);
			return (NULL);
		}
		file_key++;
		path = get_heredoc_filename(file_key);
	}
	return (path);
}

/*
** save_heredoc
** find a unique file name
** write the input into the new file
** return the path to it
*/

char		*write_heredoc_in_file(char **txt)
{
	char	*path;
	int		fd;

	if (!(path = find_uniq_filename()))
	{
		ft_strdel(txt);
		return (NULL);
	}
	if ((fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
	{
		ft_dprintf(2, "%s: an open() error occurs\n", SHELL_NAME);
		ft_strdel(txt);
		return (NULL);
	}
	if (write(fd, *txt, ft_strlen(*txt)) == -1)
		ft_dprintf(2, "%s: heredoc write error\n", SHELL_NAME);
	close(fd);
	ft_strdel(txt);
	return (path);
}
