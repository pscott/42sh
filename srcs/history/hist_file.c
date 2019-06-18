#include "history.h"
#include "input.h"
#include "cmd_parsing.h"
#include "line_editing.h"
#include "env.h"

int					open_history(const char **env, int options)
{
	int				fd;
	char			*hist_file;

	if (!(hist_file = ft_strdup(HIST_FILE)))
		clean_exit(1, 1);
	if (get_envline("HOME", (char **)env) == NULL)
	{
		ft_strdel(&hist_file);
		return (-1);
	}
	replace_tilde(&hist_file, env);
	if ((fd = open(hist_file, options, 0640)) == -1)
	{
		ft_strdel(&hist_file);
		return (-1);
	}
	ft_strdel(&hist_file);
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
		// this ?
		if (ft_strstr(tmp, "fc -s") || (ft_strstr(tmp, "fc") && ft_strstr(tmp, "-e")))
		{
			ft_strdel(&tmp);
			continue ;
		}
		if (!(line = ft_strdup_print(tmp)))
			clean_exit(1, 1);
		ft_strdel(&tmp);
		append_with_newline = ft_strjoin(&line[6], "\n");
		ft_strdel(&line);
		hist_lst = insert_right(hist_lst, append_with_newline, 1);
		ft_strdel(&append_with_newline);
		if (++id > HIST_SIZE - 2)
			break ;
	}
	ft_strdel(&tmp);
	return (hist_lst);
}

t_hist_lst			*get_history(const char **env)
{
	t_hist_lst		*hist_lst;
	int				fd;

	if (isatty(TERM_FD) == 0)
		return (NULL);
	if ((fd = open_history(env, O_RDONLY | O_NOFOLLOW)) < 0)
		return (NULL);
	hist_lst = construct_history(fd);
	close(fd);
	return (hist_lst);
}
