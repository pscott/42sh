#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

/*
** If fc -s =new, every characters of the concerned entries are
**		substituted by `new`
*/

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
	if (!(new_cmd = ft_strnew(new_cmd_len + 1)))
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

/*
** If fc -s old=, `old` is removed in the concerned entries
*/

static void	fill_new_cmd_yes_old_no_new(char **new_cmd, char *hist_curr,
	char *old_pattern, int new_cmd_len)
{
	int		i;
	int		j;
	int		old_pattern_len;

	i = 0;
	j = 0;
	old_pattern_len = ft_strlen(old_pattern);
	while (i <= new_cmd_len && hist_curr[j])
	{
		if (!ft_strnequ(&(hist_curr[j]), old_pattern, old_pattern_len))
			(*new_cmd)[i++] = hist_curr[j++];
		else
			j += old_pattern_len;
	}
}

char		*fc_s_yes_old_no_new(t_st_fc *st_fc, char *hist_curr,
	int old_cmd_len)
{
	int		old_pattern_len;
	char	*new_cmd;
	int		new_cmd_len;
	int		pattern_occurence;
	int		i;

	if (!(ft_strstr(hist_curr, st_fc->old_pattern)))
		return (NULL);
	old_pattern_len = ft_strlen(st_fc->old_pattern);
	i = 0;
	pattern_occurence = 0;
	while (hist_curr[i++])
		if (ft_strnequ(&(hist_curr[i]), st_fc->old_pattern, old_pattern_len))
			pattern_occurence++;
	new_cmd_len = old_cmd_len - pattern_occurence * old_pattern_len;
	if (new_cmd_len == 1)
		new_cmd_len = old_cmd_len;
	if (!(new_cmd = ft_strnew(new_cmd_len + 1)))
		clean_exit(1, 1);
	fill_new_cmd_yes_old_no_new(&new_cmd, hist_curr,
		st_fc->old_pattern, new_cmd_len);
	if (new_cmd && !new_cmd[0])
		new_cmd = ft_strcpy(new_cmd, hist_curr);
	return (new_cmd);
}

/*
** If fc -s old=new, `old` is substituted by `new` in the concerned entries
*/

static void	fill_new_cmd_yes_old_yes_new(t_st_fc *st_fc, char **new_cmd,
	char *hist_curr, int new_cmd_len)
{
	int		i;
	int		j;
	int		k;
	int		old_pattern_len;

	old_pattern_len = ft_strlen(st_fc->old_pattern);
	i = 0;
	j = 0;
	while (i <= new_cmd_len && hist_curr[j])
	{
		if (!ft_strnequ(&(hist_curr[j]), st_fc->old_pattern, old_pattern_len))
			(*new_cmd)[i++] = hist_curr[j++];
		else
		{
			k = 0;
			while (st_fc->new_pattern[k] && i <= new_cmd_len)
			{
				(*new_cmd)[i++] = st_fc->new_pattern[k++];
			}
			j += old_pattern_len;
		}
	}
}

char		*fc_s_yes_old_yes_new(t_st_fc *st_fc, char *hist_curr,
	int old_cmd_len)
{
	int		old_pattern_len;
	char	*new_cmd;
	int		new_cmd_len;
	int		pattern_occurence;
	int		i;

	if (!(ft_strstr(hist_curr, st_fc->old_pattern)))
		return (NULL);
	old_pattern_len = ft_strlen(st_fc->old_pattern);
	i = 0;
	pattern_occurence = 0;
	while (hist_curr[i++])
		if (ft_strnequ(&(hist_curr[i]), st_fc->old_pattern, old_pattern_len))
			pattern_occurence++;
	new_cmd_len = old_cmd_len + (pattern_occurence *
		(ft_strlen(st_fc->new_pattern) - old_pattern_len));
	if (!(new_cmd = ft_strnew(new_cmd_len + 1)))
		clean_exit(1, 1);
	fill_new_cmd_yes_old_yes_new(st_fc, &new_cmd, hist_curr, new_cmd_len);
	return (new_cmd);
}
