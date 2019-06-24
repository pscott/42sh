#include "errors.h"
#include "auto_completion.h"
#include "input.h"

static int			is_first_arg_and_exec(const char *str,
					unsigned int pos, unsigned int start)
{
	unsigned int	i;

	if (pos == 0 || str[pos - 1] == '&'
			|| str[pos - 1] == ';' || str[pos - 1] == '|')
		return (2);
	pos--;
	if (str[start] == '$' && (start == 0 || str[start - 1] != '\\'))
		return (5);
	i = 0;
	while (str
			&& (ft_is_white_space(str[i]) || ft_is_quote(str[i])) && i <= pos)
		i++;
	if (i < start)
		return (0);
	else
	{
		if (str[pos] == '\0' || ft_is_white_space(str[pos]))
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

static	char		*handle_first_arg(const char *to_find,
					const char *str, int type)
{
	char			*ret;
	t_vars			*vars;

	ret = NULL;
	vars = get_vars(NULL);
	if (type == 1)
	{
		if ((!ft_strcmp(to_find, ".") || !ft_strcmp(to_find, ".."))
			&& !(ret = ft_strjoin(to_find, "/")))
			clean_exit(1, 1);
	}
	else if (type == 2)
		auto_completion_space(vars);
	else if (type == 6)
		ret = home_directory_first_arg(to_find);
	else if (type == 7)
		ret = users_passwd(to_find);
	else if (type == 5)
		ret = varz(to_find, str);
	else if (type == 3)
		ret = handle_first_bin(vars, to_find, str);
	return (ret);
}

char				*auto_completion(char *input, unsigned int len)
{
	char			*to_find_full;
	char			*ret;
	char			*str;
	int				start;
	int				type;

	ret = NULL;
	if (!input)
		return (NULL);
	start = get_needed_values(input, len, &str, &to_find_full);
	type = is_first_arg_and_exec(to_find_full, ft_strlen(to_find_full), start);
	if (type > 0)
		ret = handle_first_arg(to_find_full + start, str + start, type);
	else if (type == 0)
	{
		ret = auto_completion_x_arg(to_find_full + start,
				str + start);
	}
//	ft_dprintf(2, "ret : |%s|, input |%s|, len %d, len_t %d, start_act %d\n", ret, input, len, len_t, start);
	format_finding_and_get_correct_ret(&ret,
		start + (len - ft_strlen(to_find_full)), input, len);
	free_two_strings(&to_find_full, &str);
	return (ret);
}
