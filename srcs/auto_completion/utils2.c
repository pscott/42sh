#include "auto_completion.h"
#include "env.h"

int				is_same_char(char a, char b)
{
	if (a == b)
		return (1);
	if (a <= 'Z' && a >= 'A' && a + 32 == b)
		return (1);
	if (a <= 'z' && a >= 'a' && a - 32 == b)
		return (1);
	return (0);
}

int				get_start_cmd_index(const char *str, int len)
{
	while (str && len >= 0)
	{
		if ((str[len] == '&' || str[len] == ';' || str[len] == '|') 
			&& (len == 0 || str[len - 1] != '\\'))
			return (len + 1);
		len--;
	}
	return (0);
}

int				get_needed_values
	(const char *input, unsigned int len, char **str, char **to_find_full)
{
	int			start_actual_word;
	int			start_cmd;

	*str = NULL;
	*to_find_full = NULL;

//	ft_dprintf(2, "\n input |%s| len %d\n", input, len);

	start_cmd = get_start_cmd_index(input, len - 1);

	if (!(*str = ft_strndup(input + start_cmd, len + 1 - start_cmd)))
		clean_exit(1, 1);
	if (!(*to_find_full = ft_strndup(input + start_cmd, len - start_cmd)))
		clean_exit(1, 1);

//	ft_dprintf(2, "\n str |%s| to_find %s\n",* str, *to_find_full);

	start_actual_word = len - start_cmd;
//	ft_dprintf(2, "\n start_act |%d|\n", start_actual_word);
	while (start_actual_word > 0
		&& !ft_is_unslashed_metachar(*to_find_full, start_actual_word, white_space)
		&& (((*to_find_full)[start_actual_word] != '\''
				&&((*to_find_full)[start_actual_word] != '\"'))
			&& (*to_find_full)[start_actual_word] != '\\'))
	{
//	ft_dprintf(2, "\n start_act |%d| et{%c} \n", start_actual_word, (*to_find_full)[start_actual_word]);
		start_actual_word--;
	}
//	ft_dprintf(2, "\n start_act |%d|\n", start_actual_word);
	while (ft_is_unslashed_metachar(*to_find_full, start_actual_word, white_space)
		|| (start_actual_word == 0
			&& ((ft_is_white_space((*to_find_full)[start_actual_word])) || ft_is_quote((*to_find_full)[start_actual_word])))
		|| (((*to_find_full)[start_actual_word] == '\''
				 || ((*to_find_full)[start_actual_word] == '\"'))
			&& (*to_find_full)[start_actual_word] != '\\'))
		start_actual_word++;

//	ft_dprintf(2, "\n start_act |%d|\n", start_actual_word);

	/*
//	*len = *len - start_cmd;
//	if (start_cmd > 0)
//		start_cmd--;
//	start_actual_word = *len;
//	if (len > 0
//		&& ft_is_unslashed_metachar(*to_find_full, len - 1, white_space))
//		start_actual_word--;
	while (start_actual_word > start_cmd
		&& !ft_is_unslashed_metachar(*to_find_full,
			start_actual_word, white_space))
	//	&& !ft_is_unslashed_metachar(*to_find_full,
	//		start_actual_word, separator))
		start_actual_word--;
		|| (ft_is_unslashed_metachar(*to_find_full, start_actual_word,
				white_space) || (start_actual_word == 0 && ft_strchr("&;|", (*to_find_full)[0]))))
		*/
	return (start_actual_word);
}

int				get_path(char ***path, t_vars *vars)
{
	char		*tmpath;

	if (!vars || !vars->env_vars)
		return (0);
	if (!(tmpath = get_envline_value("PATH", vars->env_vars)))
	{
		*path = NULL;
		return (1);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		clean_exit(1, 1);
	return (0);
}

int				free_two_strings(char **s1, char **s2)
{
	if (s1)
		ft_strdel(s1);
	if (s2)
		ft_strdel(s2);
	return (0);
}

int				free_four_strings(char **s1, char **s2, char **s3, char **s4)
{
	free_two_strings(s1, s2);
	free_two_strings(s3, s4);
	return (0);
}
