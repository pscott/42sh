#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

int					fc_edit_open_file(t_st_cmd *st_cmd, t_st_fc *st_fc,
	char **tmp_file)
{
	int				tmp_file_fd;
	int				diff;
	t_hist_lst		*hist_curr;

	if (!(*tmp_file = find_unique_filename(FC_EDIT_FILENAME)))
		return (-1);
	if ((tmp_file_fd = open(*tmp_file, O_CREAT | O_RDWR | O_EXCL, 0666)) == -1)
	{
		ft_strdel(tmp_file);
		return (print_errors(-1, ERR_OPEN_FC_STR, NULL));
	}


	if (!ft_strchr(st_fc->flag, 'r'))
		diff = *st_cmd->hist_len - st_fc->i_first + 1;
	else
		diff = *st_cmd->hist_len - st_fc->i_last + 1;

	hist_curr = get_end_lst(st_cmd->hist_lst);
	while (diff--)
		hist_curr = hist_curr->prev;
	ft_dprintf(2, "oioio %s\n", hist_curr->txt);
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

int					fc_edit_open_editor(t_st_cmd *st_cmd, t_st_fc *st_fc,
	char **tmp_file, int tmp_file_fd)
{
	char			**argv;
	int				ret;

	(void)st_cmd;
	(void)tmp_file_fd;
	if (!(argv = (char**)malloc(sizeof(char*) * 3)))
		return (1);
	if ((!st_fc->editor && !(argv[0] = ft_strdup("vim")))
		|| (st_fc->editor && (!(argv[0] = ft_strdup(st_fc->editor)))))
		clean_exit(1, 1);
	if (!(argv[1] = ft_strdup(*tmp_file)))
		clean_exit(1, 1);
	argv[2] = NULL;
	ret = exec_bin(argv);
	ft_free_ntab(argv);
	return (ret);
}
