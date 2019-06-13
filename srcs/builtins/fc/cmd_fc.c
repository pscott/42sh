#include "errors.h"
#include "ftsh.h"
#include "builtins.h"

int					case_fc_display(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	int				i_last_real;
	int				i_curr;
	t_hist_lst		hist_curr;

	
//	i_last_real = (*st_cmd->hist_len) > st_fc->i_last
// ici?		? st_fc->i_last : (*st_cmd->hist_len);
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

char		*fc_s_no_old_yes_new(t_st_fc *st_fc, t_hist_lst hist_curr,
	int old_cmd_len)
{
	int		i;
	int		j;
	int		len_pattern;
	char	*new_cmd;
	int		new_cmd_len;

	len_pattern = ft_strlen(st_fc->new);
	new_cmd_len = old_cmd_len * len_pattern;
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);
	i = 0;
	while (i < new_cmd_len)
	{
		j = 0;
		while (j < len_pattern)
		{
			new_cmd[i++] = st_fc->new[j++];	
		}
	}
	return (new_cmd);
}

char		*fc_s_yes_old_no_new(t_st_fc *st_fc, t_hist_lst hist_curr,
	int old_cmd_len)
{
	int		old_pattern_len;
	char	*new_cmd;
	int		new_cmd_len;
	int		pattern_occurence;
	int		i;
	int		j;

	if (!(ft_strstr(hist_curr->txt, st_fc->old)))
		return (NULL);
	old_pattern_len = ft_strlen(st_fc->old);
	i = 0;
	pattern_occurence = 0;
	while (hist_curr->txt[i++])
		if (ftstrneq(&(hist_curr->txt[i]), st_fc->old, old_pattern_len))//good len?
			pattern_occurence++;
	new_cmd_len = old_cmd_len - pattern_occurence * old_pattern_len;
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);
	i = -1;
	j = -1;
	while (++i < new_cmd_len && hist_curr->txt[++j])
	{
		if (!ft_strneq(&(hist_curr->txt[i]), st_fc->old, old_pattern_len))
			new_cmd[i] = hist_curr->txt[j];
		else
			j += old_pattern_len;
	}
	return (new_cmd);
}


char		*fc_s_yes_old_yes_new(t_st_fc *st_fc, t_hist_lst hist_curr,
	int old_cmd_len)
{
	int		old_pattern_len;
	int		new_pattern_len;
	char	*new_cmd;
	int		new_cmd_len;
	int		pattern_occurence;
	int		i;
	int		j;

	if (!(ft_strstr(hist_curr->txt, st_fc->old)))
		return (NULL);
	old_pattern_len = ft_strlen(st_fc->old);
	new_pattern_len = ft_strlen(st_fc->new);
	i = 0;
	pattern_occurence = 0;
	while (hist_curr->txt[i++])
		if (ftstrneq(&(hist_curr->txt[i]), st_fc->old, old_pattern_len))//good len?
			pattern_occurence++;
	new_cmd_len = old_cmd_len + (pattern_occurence * (ft_strlen(st_fc->new) - old_pattern_len));
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);
	i = -1;
	j = -1;
	int k;
	k = -1;
	while (++i < new_cmd_len && hist_curr->txt[++j])
	{
		if (!ft_strneq(&(hist_curr->txt[i]), st_fc->old, old_pattern_len))
			new_cmd[i] = hist_curr->txt[j];
		else
		{
			while (st_fc->new[++k] && new_cmd[++i])
			{
				new_cmd[i] = st_fc->new[k];
				j++;
			}
		}
	}
	return (new_cmd);
}

static int			case_fc_exec(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	char			*new_cmd;
	int				new_cmd_len;
	int				old_cmd_len;
	t_hist_lst		hist_curr;

	if (!st_cmd->hist_lst)
		return (-1);
	hist_curr = (*st_cmd->hist_lst);
	while (hist_curr.prev && st_fc->i_first--)//i_first doit avoir ete set mais si pas present
		hist_curr = (*hist_curr.prev);
	old_cmd_len = ft_strlen(hist_curr->txt);
	if (!st_fc->old && !st_fc->new)
		return (0);
	else if (!st_fc->old && st_fc->new)
		new_cmd = fc_s_no_old_yes_new(st_fc, hist_curr, old_cmd_len);
	else if (st_fc->old && !st_fc->new)
		new_cmd = fc_s_yes_old_no_new(st_fc, hist_curr, old_cmd_len);// check si empty
	else if (st_fc->old && st_fc->new)
		new_cmd = fc_s_yes_old_yes_new(st_fc, hist_curr, old_cmd_len);




	if (new_cmd)//&& new_cmd[0]?
	{
		free_st_txt(&st_cmd->st_txt);
		st_cmd->st_txt->txt = new_cmd;
	}
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
	if (st_fc->old_p)
		free(st_fc->old_p);
	if (st_fc->new_p)
		if (st_fc->new_p);
	//free st_Fc?
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

	if (st_fc.flags[0] == 's')
		ret = case_fc_exec(st_cmd, &st_fc);
	else if (ft_strchr(st_fc.flag, 'l'))
		ret = case_fc_display(st_cmd, &st_fc);/*
												 else
												 ret = case_fc_editor(st_cmd, &st_fc);
												 */
	return (ret);
}
