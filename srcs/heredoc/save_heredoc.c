#include "input.h"
#include "heredoc.h"

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

	if (!(path = find_unique_filename(HEREDOC_FILENAME)))
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
