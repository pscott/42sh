#include "errors.h"
#include "ftsh.h"
#include "builtins.h"

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

char		*fc_s_no_old_yes_new(t_st_fc *st_fc,
	int old_cmd_len)
{
	int		i;
	int		j;
	int		len_pattern;
	char	*new_cmd;
	int		new_cmd_len;

	len_pattern = ft_strlen(st_fc->new_pattern);
	new_cmd_len = old_cmd_len * len_pattern;
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);
	i = 0;
	while (i < new_cmd_len)
	{
		j = 0;
		while (j < len_pattern)
		{
			new_cmd[i++] = st_fc->new_pattern[j++];	
		}
	}
	return (new_cmd);
}

char		*fc_s_yes_old_no_new(t_st_fc *st_fc, char *hist_curr,
	int old_cmd_len)
{
	int		old_pattern_len;
	char	*new_cmd;
	int		new_cmd_len;
	int		pattern_occurence;
	int		i;
	int		j;

	if (!(ft_strstr(hist_curr, st_fc->old_pattern)))
		return (NULL);
	old_pattern_len = ft_strlen(st_fc->old_pattern);
	i = 0;
	pattern_occurence = 0;
	while (hist_curr[i++])
		if (ft_strnequ(&(hist_curr[i]), st_fc->old_pattern, old_pattern_len))//good len?
			pattern_occurence++;
	new_cmd_len = old_cmd_len - pattern_occurence * old_pattern_len;
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);
	i = 0;
	j = 0;
	while (i <= new_cmd_len && hist_curr[j])
	{
		/*
	ft_dprintf(2, "\n\n-----------INSIDE------------\n\n i : %d\n j : %d\n, hist_curr :|%s|\n old_pattern : |%s|\n old_pattern_len : %d\n new_cmd_len : %d", i, j, hist_curr, st_fc->old_pattern, old_pattern_len, new_cmd_len);
*/
		if (!ft_strnequ(&(hist_curr[j]), st_fc->old_pattern, old_pattern_len))
			new_cmd[i++] = hist_curr[j++];
		else
			j += old_pattern_len;
	}
	return (new_cmd);
}


char		*fc_s_yes_old_yes_new(t_st_fc *st_fc, char *hist_curr,
	int old_cmd_len)
{
	int		old_pattern_len;
	int		new_pattern_len;
	char	*new_cmd;
	int		new_cmd_len;
	int		pattern_occurence;
	int		i;
	int		j;

	if (!(ft_strstr(hist_curr, st_fc->old_pattern)))
		return (NULL);
	old_pattern_len = ft_strlen(st_fc->old_pattern);
	new_pattern_len = ft_strlen(st_fc->new_pattern);
	i = 0;
	pattern_occurence = 0;
	while (hist_curr[i++])
		if (ft_strnequ(&(hist_curr[i]), st_fc->old_pattern, old_pattern_len))//good len?
			pattern_occurence++;
	new_cmd_len = old_cmd_len + (pattern_occurence * (ft_strlen(st_fc->new_pattern) - old_pattern_len));
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);
	i = 0;
	j = 0;
	int k;
	while (i <= new_cmd_len && hist_curr[j])
	{
		/*
	ft_dprintf(2, "\n\n-----------INSIDE------------\n\n i : %d\n j : %d\n, hist_curr :|%s|\n old_pattern : |%s|\n old_pattern_len : %d\n new_cmd_len : %d", i, j, hist_curr, st_fc->old_pattern, old_pattern_len, new_cmd_len);
	*/
		if (!ft_strnequ(&(hist_curr[j]), st_fc->old_pattern, old_pattern_len))
			new_cmd[i++] = hist_curr[j++];
		else
		{
			k = 0;
			while (st_fc->new_pattern[k] && i<= new_cmd_len)
			{
				new_cmd[i++] = st_fc->new_pattern[k++];
			}
			j++;
		}
	}
	return (new_cmd);
}

static int			case_fc_exec(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	char			*new_cmd;
	int				old_cmd_len;
	t_hist_lst		hist_curr;
	int				diff;
	char			*histo_real_entry;

	  ft_dprintf(2, "i_first: %d\ni_last: %d\n", st_fc->i_first, st_fc->i_last);
	  ft_dprintf(2, "old: %s\nnew: %s\n", st_fc->old_pattern, st_fc->new_pattern);
	  ft_dprintf(2, "editor:%s\n", st_fc->editor);
	  
	  new_cmd = NULL;

	diff = *st_cmd->hist_len - st_fc->i_first;

	if (!st_cmd->hist_lst)
		return (-1);
	hist_curr = (*st_cmd->hist_lst);
	while (hist_curr.prev && diff--)//i_first doit avoir ete set mais si pas present
		hist_curr = (*hist_curr.prev);
	hist_curr = (*hist_curr.prev);//car maintenant, fc_s rentre dans l'histo et devrait pas
	old_cmd_len = ft_strlen_char(hist_curr.txt, '\n');
	histo_real_entry = ft_strndup(hist_curr.txt, old_cmd_len);
	if (!st_fc->old_pattern[0] && !st_fc->new_pattern[0])
	{
	ft_dprintf(2, "\n---NO OLD NO NEW---\n", new_cmd);
		return (0);
	}
	else if (!st_fc->old_pattern[0] && st_fc->new_pattern[0])
	{
	ft_dprintf(2, "\n---NO OLD YES NEW---\n", new_cmd);
	ft_dprintf(2, "\n---%s---\n", hist_curr.txt);
	ft_dprintf(2, "\n---|%d|---\n", *st_cmd->hist_len);
		new_cmd = fc_s_no_old_yes_new(st_fc, old_cmd_len);
	}
	else if (st_fc->old_pattern[0] && !st_fc->new_pattern[0])
	{
	ft_dprintf(2, "\n---YES OLD NO NEW---\n", new_cmd);
		new_cmd = fc_s_yes_old_no_new(st_fc, histo_real_entry, old_cmd_len);// check si empty
	}
	else if (st_fc->old_pattern && st_fc->new_pattern)
	{
	ft_dprintf(2, "\n---YES OLD YES NEW---\n", new_cmd);
		new_cmd = fc_s_yes_old_yes_new(st_fc, histo_real_entry, old_cmd_len);
	}



	ft_dprintf(2, "\n[%s]\n", new_cmd);
	if (new_cmd)//&& new_cmd[0]?
	{
		free(st_cmd->st_txt->txt);
		if (!(st_cmd->st_txt->txt = ft_strdup(new_cmd)))
			clean_exit(1, 1);
		free(new_cmd);
	}
	ft_dprintf(2, "[%s]\n", st_cmd->st_txt->txt);
	return (0);
}

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

static int			fc_edit_open_file(t_st_cmd *st_cmd, t_st_fc *st_fc, char **tmp_file)
{
	int				tmp_file_fd;
	int				diff;
	t_hist_lst		hist_curr;


	if (!(*tmp_file = find_unique_filename(FC_EDIT_FILENAME)))
		return (-1);
	if ((tmp_file_fd = open(*tmp_file, OCREAT | O_RDWR | O_EXCL, 0666)) == -1)
	{
		ft_dprintf(2, "%s: fc: an open() error occured\n", SHELL_NAME);
		ft_strdel(tmp_file);
		return (-1);
	}
	diff = st_cmd->hist_len - st_fc->i_first;
	hist_curr = (*st_cmd->hist_lst);
	while (diff--)
		hist_curr = hist_curr.prev;
	diff = st_fc->i_last - st_fc->i_first;
	while (diff--)
	{
		ft_dprintf(tmp_file_fd, "%s", hist_curr.txt);
		hist_curr = hist_curr.next;
	}
	if (close(fd) == -1)
		return (-1);
	return (tmp_file_fd);
}

static int			fc_edit_open_editor(t_st_cmd *st_cmd, t_st_fc *st_fc,
	char **tmp_file, int tmp_file_fd)
{
	// editor need to be set before !
	char			**argv;
	int				ret;

	if (!(argv = (char**)malloc(sizeof(char*) * 3)))
		return (-1);
	if (!(argv[0] = ft_strdup(st_fc->editor)))
	{
		free(argv);
		return (-1);
	}
	if (!(argv[1] = ft_strdup(st_fc->*tmp_file)))
	{
		free(argv[0]);
		free(argv);
		return (-1);
	}
	argv[2] = NULL;
	ret = exec_bin(argv);
	return (ret);
}

static int			case_fc_editor(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	int				tmp_file_fd;
	char			*tmp_file;
	

	if ((tmp_file_fd = fc_edit_open_file(st_cmd, st_fc, &tmp_file)) == -1)
		return (1);
	if ((fc_edit_open_editor(st_cmd, st_fc, &tmp_file, tmp_file_fd)) == -1)
	{
		ft_strdel(&tmp_file);
		return (1);
	}
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

	if (st_fc.flag[0] == 's')
		ret = case_fc_exec(st_cmd, &st_fc);
	else if (ft_strchr(st_fc.flag, 'l'))
		ret = case_fc_display(st_cmd, &st_fc);
	else
		ret = case_fc_editor(st_cmd, &st_fc);
	return (ret);
}
