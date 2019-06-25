#include "input.h"

/*
** get_heredoc_finename or tmp_filename
** concatenate the default type_filename with the given key
** and return it
*/

static char	*get_tmp_filename(unsigned int file_key, char *type)
{
	char			*path;
	char			*file_key_str;

	if (!(path = ft_strnew(ft_strlen(type) + MAX_INT_LEN)))
		clean_exit(1, MALLOC_ERR);
	ft_strcpy(path, type);
	if (!(file_key_str = ft_itoa((int)file_key)))
		clean_exit(1, MALLOC_ERR);
	ft_strcpy(&path[ft_strlen(type)], file_key_str);
	ft_memdel((void*)&file_key_str);
	return (path);
}

/*
** find_unique_filename
** find an unused filename
** and returned it
*/

char		*find_unique_filename(char *type)
{
	char			*path;
	unsigned int	file_key;

	file_key = 0;
	path = get_tmp_filename(file_key, type);
	while (access(path, F_OK) == 0)
	{
		ft_strdel(&path);
		if (file_key == UINT_MAX)
		{
			if (ft_strequ(type, HEREDOC_FILENAME))
				ft_dprintf(2,
					"%s: can't create heredoc temporary file(max UINT)\n",
					SHELL_NAME);
			else if (ft_strequ(type, FC_EDIT_FILENAME))
				ft_dprintf(2,
					"%s: can't create history edit temporary file(max UINT)\n",
					SHELL_NAME);
			return (NULL);
		}
		file_key++;
		path = get_tmp_filename(file_key, type);
	}
	return (path);
}
