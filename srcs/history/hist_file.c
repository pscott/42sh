#include "history.h"
#include "input.h"
#include "cmd_parsing.h"
#include "get_next_line.h"

int					open_history(const char **env, int options)
{
	int				fd;
	char			*hist_file;

	if (!(hist_file = ft_strdup(HIST_FILE)))
		ERROR_MEM;
	replace_tilde(&hist_file, env);
	if ((fd = open(hist_file, options, 0640)) == -1)
	{
		ft_memdel((void*)&hist_file);
		return (-1);
	}
	ft_memdel((void*)&hist_file);
	return (fd);
}

static t_hist_lst	*construct_history(int fd)
{
	size_t			id;
	char			*tmp;
	char			*append_with_newline;
	char			*line;
	t_hist_lst		*hist_lst;

	id = 0;
	hist_lst = NULL;
	tmp = NULL;
	while ((get_next_line(fd, &tmp) > 0) && (tmp && ft_printable_len(tmp) > 6))
	{
		if (!(line = ft_strdup_print(tmp)))
			ERROR_MEM;
		ft_strdel(&tmp);
		append_with_newline = ft_strjoin(&line[6], "\n");
		ft_strdel(&line);
		hist_lst = insert_right(hist_lst, append_with_newline, 1);
		ft_strdel(&append_with_newline);
		id++;
	}
	if (tmp)
		ft_memdel((void*)&tmp);
	return (hist_lst);
}

t_hist_lst			*get_history(const char **env)
{
	t_hist_lst		*hist_lst;
	int				fd;

	if (isatty(STDIN_FILENO) == 0)
		return (NULL);
	if ((fd = open_history(env, O_RDONLY)) < 0)
		return (NULL);
	hist_lst = construct_history(fd);
	close(fd);
	return (hist_lst);
}
