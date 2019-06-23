#include "errors.h"
#include "auto_completion.h"
#include "input.h"

static int			is_first_arg_and_exec(const char *str,
					unsigned int cursor_pos, unsigned int start_actual_word)
{
	unsigned int	i;

	if (cursor_pos == 0 || str[cursor_pos - 1] == '&' || str[cursor_pos - 1] == ';' || str[cursor_pos - 1] == '|')
		return (2);
	cursor_pos--;
	if (str[start_actual_word] == '$' && (start_actual_word == 0 || str[start_actual_word - 1] != '\\'))
		return (5);
	i = 0;
	while (str && (ft_is_white_space(str[i]) || ft_is_quote(str[i])) && i <= cursor_pos)
		i++;
	if (i < start_actual_word)
		return (0);
	else
	{
		if (str[cursor_pos] == '\0' || ft_is_white_space(str[cursor_pos]))
			return (2);
		if (str[i] == '~' && str[i + 1] && str[i + 1] == '/')
			return (6);
		else if (str[i] == '~' && (!str[i + 1] || str[i + 1] != '/'))
			return (7);
		else if (str[i] == '$')
			return (5);
		else
			return (3);
	}
}

static	char		*handle_first_arg_dot_tilde(int type, const char *to_find,
					const char *str)
{
	char			*ret;

	ret = NULL;
	if (type == 1)
	{
		if ((!ft_strcmp(to_find, ".") || !ft_strcmp(to_find, ".."))
			&& !(ret = ft_strjoin(to_find, "/")))
			clean_exit(1, 1);
	}
	else if (type == 6)
		ret = home_directory_first_arg(to_find);
	else if (type == 7)
		ret = users_passwd(to_find);
	else if (type == 5)
		ret = varz(to_find, str);
	return (ret);
}

static char			*handle_first_bin(t_vars *vars, const char *to_find,
					const char *str)
{
	char			*ret;

	ret = NULL;
	if (!(ret = auto_completion_bin(vars, to_find, str)))
	{
		if (!ft_strncmp(to_find, ".", 2) || !ft_strncmp(to_find, "..", 3))
		{
			if (!(ret = ft_strjoin(to_find, "/")))
				clean_exit(1, 1);
		}
		else if (!ft_strchr(to_find, '/'))
			ret = get_dirs_first_arg(".", to_find, ft_strlen(to_find));
		else
			ret = search_dirs_and_exe(to_find);
	}
	return (ret);
}

char				*auto_completion(char *input, unsigned int len,
					t_vars *vars)
{
	char			*to_find_full;
	char			*ret;
	char			*tmp;
	char			*str;
	int				start_actual_word;
	int				len_t;

	ret = NULL;
	tmp = NULL;
	if (!input)
		return (NULL);
	start_actual_word = get_needed_values(input, len, &str, &to_find_full);
	len_t = ft_strlen(to_find_full);

	/*
	ft_dprintf(2, "\n-------------||%s||-----------\n", to_find_full);
	ft_dprintf(2, "\n-------------||%d||-----------\n", start_actual_word);
*/
	if (is_first_arg_and_exec(to_find_full, len_t, start_actual_word) == 3)
		ret = handle_first_bin(vars, to_find_full + start_actual_word,
				str + start_actual_word);
	else if (is_first_arg_and_exec(to_find_full, len_t, start_actual_word) == 2)
		auto_completion_space(vars);
	else if (is_first_arg_and_exec(to_find_full, len_t, start_actual_word))
		ret = handle_first_arg_dot_tilde(is_first_arg_and_exec(to_find_full, len_t,
					start_actual_word), to_find_full + start_actual_word, str + start_actual_word);
	else if (!is_first_arg_and_exec(to_find_full, len_t, start_actual_word))
	{
		ret = auto_completion_x_arg(to_find_full + start_actual_word,
				str + start_actual_word);
	}
	
//	ft_dprintf(2, "ret : |%s|, input |%s|, len %d, len_t %d, start_act %d\n", ret, input, len, len_t, start_actual_word);
	
	format_finding_and_get_correct_ret(&ret, start_actual_word + (len - len_t), input, len);
	free_two_strings(&to_find_full, &str);
	return (ret);
}
