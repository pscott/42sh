#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

static void			free_st_fc(t_st_fc *st_fc)
{
	if (st_fc->first)
		free(st_fc->first);
	if (st_fc->last)
		free(st_fc->last);
	if (st_fc->editor)
		free(st_fc->editor);
	if (st_fc->old_pattern)
		free(st_fc->old_pattern);
	if (st_fc->new_pattern)
		free(st_fc->new_pattern);
	//free st_Fc?
}

int					case_fc_display(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	int				i_last_real;
	int				i_curr;
	t_hist_lst		hist_curr;

	
	i_last_real = (*st_cmd->hist_len) > st_fc->i_last
/* ici?*/		? st_fc->i_last : (*st_cmd->hist_len);
	i_curr = st_fc->i_first;
	hist_curr = (*st_cmd->hist_lst);
	while (hist_curr.prev && i_curr--)
		hist_curr = (*hist_curr.prev);
	i_curr = st_fc->i_first;
	while (i_curr <= i_last_real && hist_curr.next)
	{
		if (!ft_strchr(st_fc->flag, 'n'))
			ft_putnbr(i_curr);
		//case multi ligne?
		ft_printf("\t%s", hist_curr.txt);
		i_curr++;
		hist_curr = (*hist_curr.next);
	}
	return (0);
}

static int			case_fc_substitute(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	char			*new_cmd;
	int				old_cmd_len;
	t_hist_lst		hist_curr;
	int				diff;
	char			*histo_real_entry;

	new_cmd = NULL;
	diff = *st_cmd->hist_len - st_fc->i_first;
	if (!st_cmd->hist_lst)
		return (-1);
	hist_curr = (*st_cmd->hist_lst);
	while (hist_curr.prev && diff--)
		hist_curr = (*hist_curr.prev);
	hist_curr = (*hist_curr.prev);//car maintenant, fc_s rentre dans l'histo et devrait pas --> REMOVE ENSUITE
	old_cmd_len = ft_strlen_char(hist_curr.txt, '\n');
	histo_real_entry = ft_strndup(hist_curr.txt, old_cmd_len);
	if (!st_fc->old_pattern[0] && !st_fc->new_pattern[0])
		return (0);
	else if (!st_fc->old_pattern[0] && st_fc->new_pattern[0])
	{
		new_cmd = fc_s_no_old_yes_new(st_fc, old_cmd_len);
	}
	else if (st_fc->old_pattern[0] && !st_fc->new_pattern[0])
		new_cmd = fc_s_yes_old_no_new(st_fc, histo_real_entry, old_cmd_len);// check si empty
	else if (st_fc->old_pattern && st_fc->new_pattern)
		new_cmd = fc_s_yes_old_yes_new(st_fc, histo_real_entry, old_cmd_len);
	//
	//en gros, need to split la fonction pour envoyer dans exec_bin comme -e
	//
	if (new_cmd)//&& new_cmd[0]?
	{
		free(st_cmd->st_txt->txt);
		if (!(st_cmd->st_txt->txt = ft_strdup(new_cmd)))
			clean_exit(1, 1);
		free(new_cmd);
	}
	return (0);
}

static int			case_fc_editor(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	int				tmp_file_fd;
	char			*tmp_file;
	

	if ((tmp_file_fd = fc_edit_open_file(st_cmd, st_fc, &tmp_file)) == -1)
		return (1);
//	/*
	if ((fc_edit_open_editor(st_cmd, st_fc, &tmp_file, tmp_file_fd)) == 1)
	{
		ft_strdel(&tmp_file);
		return (1);
	}
	fc_edit_execute_cmd(tmp_file);
	return (0);
}

/*
 **	Init struct_fc depending on options, then execute the adequate cqse.
 **	Returns 0 on success.
 **	Returns 1 on failure.
 */

int					case_fc(char **argv)
{
	t_st_fc			st_fc;
	t_st_cmd		*st_cmd;
	int				ret;

	ft_bzero(&st_fc, sizeof(st_fc));
	st_cmd = get_st_cmd(NULL);

	if ((ret = init_st_fc(st_cmd, &st_fc, argv)) == 1)
	{
		free_st_fc(&st_fc);
		return (ret);
	}
	ret = 0;

/*	
	  ft_dprintf(2, "first: %s\nlast: %s\n", st_fc.first, st_fc.last);
	  ft_dprintf(2, "i_first: %d\ni_last: %d\n", st_fc.i_first, st_fc.i_last);
	  ft_dprintf(2, "old: %s\nnew: %s\n", st_fc.old_pattern, st_fc.new_pattern);
	  ft_dprintf(2, "editor:%s\n", st_fc.editor);
 
*/

	if (st_fc.flag[0] == 's')
		ret = case_fc_substitute(st_cmd, &st_fc);
	else if (ft_strchr(st_fc.flag, 'l'))//only THIS case is put in history
		ret = case_fc_display(st_cmd, &st_fc);
	else
		ret = case_fc_editor(st_cmd, &st_fc);
	return (ret);
}
