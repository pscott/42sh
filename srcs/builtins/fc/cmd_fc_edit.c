#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"
#include "env.h"

static int			get_needed_values(char **tmp_file, int *tmp_file_fd)
{
	if (!(*tmp_file = find_unique_filename(FC_EDIT_FILENAME)))
		return (-1);
	if ((*tmp_file_fd = open(*tmp_file, O_CREAT | O_RDWR | O_EXCL, 0666)) == -1)
	{
		ft_strdel(tmp_file);
		return (print_errors(-1, ERR_OPEN_FC_STR, NULL));
	}
	return (0);
}

int					fc_edit_open_file(t_st_cmd *st_cmd, t_st_fc *st_fc,
	char **tmp_file)
{
	int				tmp_file_fd;
	int				diff;
	t_hist_lst		*hist_curr;

	if (get_needed_values(tmp_file, &tmp_file_fd) < 0)
		return (-1);
	if (!ft_strchr(st_fc->flag, 'r'))
		diff = *st_cmd->hist_len - st_fc->i_first + 1;
	else
		diff = *st_cmd->hist_len - st_fc->i_last + 1;
	hist_curr = get_end_lst(st_cmd->hist_lst);
	while (diff--)
		hist_curr = hist_curr->prev;
	diff = st_fc->i_last - st_fc->i_first + 1;
	while (diff--)
	{
		ft_dprintf(tmp_file_fd, "%s", hist_curr->txt);
		if (!ft_strchr(st_fc->flag, 'r') && hist_curr->next)
			hist_curr = hist_curr->next;
		else if (hist_curr->prev)
			hist_curr = hist_curr->prev;
	}
	if (close(tmp_file_fd) == -1)
		return (-1);
	return (tmp_file_fd);
}

static char			*get_editor(t_st_fc *st_fc)
{
	char			*ret;
	char			*tmp;
	t_vars			*vars;

	if (st_fc->editor)
		ret = ft_strdup(st_fc->editor);
	else
	{
		vars = get_vars(NULL);
		if ((tmp = get_envline_value("FCEDIT", vars->env_vars)) != NULL)
			ret = ft_strdup(tmp);
		else
			ret = ft_strdup("ed");
	}
	if (ret == NULL)
		clean_exit(1, MALLOC_ERR);
	return (ret);
}

int					fc_edit_open_editor(t_st_cmd *st_cmd, t_st_fc *st_fc,
	char **tmp_file, int tmp_file_fd)
{
	char			**argv;
	int				ret;

	(void)st_cmd;
	(void)tmp_file_fd;
	if (!(argv = (char**)malloc(sizeof(char*) * 3)))
		return (1);
	argv[0] = get_editor(st_fc);
	if (!(argv[1] = ft_strdup(*tmp_file)))
		clean_exit(1, MALLOC_ERR);
	argv[2] = NULL;
	ret = exec_bin(argv);
	ft_free_ntab(argv);
	return (ret);
}
