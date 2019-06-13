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

/*
** If fc -s old=, `old` is removed in the concerned entries
*/

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
		if (ft_strnequ(&(hist_curr[i]), st_fc->old_pattern, old_pattern_len))//check good len?
			pattern_occurence++;
	new_cmd_len = old_cmd_len - pattern_occurence * old_pattern_len;
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);

	// split here

	i = 0;
	j = 0;
	while (i <= new_cmd_len && hist_curr[j])
	{
		if (!ft_strnequ(&(hist_curr[j]), st_fc->old_pattern, old_pattern_len))
			new_cmd[i++] = hist_curr[j++];
		else
			j += old_pattern_len;
	}
	return (new_cmd);
}

/*
** If fc -s old=new, `old` is substituted by `new` in the concerned entries
*/


// need to split this fun - should be easy

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
		if (ft_strnequ(&(hist_curr[i]), st_fc->old_pattern, old_pattern_len))//check if good len?
			pattern_occurence++;
	new_cmd_len = old_cmd_len + (pattern_occurence * (ft_strlen(st_fc->new_pattern) - old_pattern_len));
	if (!(new_cmd = ft_strnew(new_cmd_len)))
		clean_exit(1, 1);

	//split here

	i = 0;
	j = 0;
	int k;
	while (i <= new_cmd_len && hist_curr[j])
	{
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
