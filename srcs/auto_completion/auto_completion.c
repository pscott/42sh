
#include "libft.h"
#include "errors.h"
#include "line_editing.h"
#include "get_next_line_2.h"

/* 
** compare start_actual_word (== len) and first word of the input. if ==, then its first arg of input
*/

static int			is_first_arg_and_exec(const char *str, unsigned int cursor_pos, unsigned int start_actual_word)
{
	unsigned int	i;

	i = 0;

	if (cursor_pos == 0)
		return (2);
	else
		cursor_pos--;
	while (str && ft_is_white_space(str[i]) && i <= cursor_pos)
		i++;
	if (i < start_actual_word)
			return (0);
	else
	{
		if (str[cursor_pos] == '\0' || ft_is_white_space(str[cursor_pos]))
			return (2);
		else if (str[i] == '~' && str[i + 1] && str[i + 1] == '/')
				return (6);
		else if (str[i] == '~' && (!str[i + 1] || str[i + 1] != '/'))
				return (7);
		else if (str[i] == '$')
			return (5);
		else
			return (3);
	}
}

static char			*handle_x_arg(char *input, char *to_find_and_next_char)
{
	char			*path;
	char			*to_find;
	char			*tmp;
	char			*tmp2;
	char			*ret_str;
	t_auto_comp		*match;

	to_find = NULL;
	path = NULL;
	ret_str = NULL;
	match = NULL;
	tmp = NULL;
	tmp2 = NULL;
	if (input && input[0] && ft_strchr(input, '/'))
		tmp = ft_strndup(input, ft_strlen(input) - ft_strlen(ft_strrchr(input, '/') + 1));
	get_path_file_and_to_find(input, &path, &to_find);
	if (!to_find[0] || ft_is_white_space(to_find[0]))
		find_all_except_dots(path, &match); 
	else
		find_all_match(path, &match, to_find, to_find_and_next_char);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	else if (!(ret_str = ft_strdup(to_find)))
		ERROR_MEM
	free_four_strings(&tmp, &ret_str, &path, &to_find);
	return (tmp2);
}

static unsigned int	ft_strlen_char(const char *line, char c)
{
	unsigned int	i;

	i = 0;
	while (line && line[i] && line[i] != c && line[i] != '\0')
		i++;
	return (i);
}

static void			get_user_name(char **users, const char *line)
{
	char			*tmp;
	char			*tmp2;
	struct passwd	*infos;
	struct stat		file_infos;

	tmp = NULL;
	tmp2 = NULL;
	infos = NULL;
	if (!(tmp = ft_strndup(line, ft_strlen_char(line, ':'))))
		ERROR_MEM
	if (!(tmp2 = ft_strjoin("~", tmp)))
		ERROR_MEM
	infos = getpwnam(tmp);
	if ((stat(infos->pw_dir, &file_infos) != -1))
	{
		if (S_ISDIR(file_infos.st_mode))
		{
			if (!((*users) = ft_strjoin(tmp2, "/")))
				ERROR_MEM
		}
	}
	else if (!(*users = ft_strdup(tmp2)))
		ERROR_MEM
	free_two_strings(&tmp, &tmp2);
}

static int			get_users_list(t_auto_comp **match, const char *to_find)
{
	int				fd;
	char			*line;
	int				ret;
	char			*users;
	char			*tmp;

	line = NULL;
	users = NULL;
	tmp = NULL;
	fd = open("/etc/passwd", 0);
	while (((ret = get_next_line_2(fd, &line)) != -1))
	{
		if (line && line[0] && line[0] != '#' && (!to_find[0] || !strncmp(to_find, line, ft_strlen(to_find))))
		{
			get_user_name(&users, line);
			if (users == NULL)
				users = ft_strnew(1);
			create_match_link(match, users);
			ft_strdel(&users);
		}
		if (!ret)
			break ;
	}
	return (0);
}

char				*users_passwd(const char *to_find)
{
	t_auto_comp		*match;
	char			*ret_str;

	match = NULL;
	ret_str = NULL;
	get_users_list(&match, to_find + 1);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	return (ret_str);
}

char				*handle_first_arg_dot_tilde(int type, const char *to_find)
{
	char			*ret;

	ret = NULL;
	if (type == 1) 
	{
		if ((!ft_strcmp(to_find, ".") || !ft_strcmp(to_find, "..")) && !(ret = ft_strjoin(to_find, "/")))
			ERROR_MEM
	}
	else if (type == 6)
		ret = home_directory_first_arg(to_find);
	else if (type == 7)
		ret = users_passwd(to_find);
	return (ret);
}

static char			*handle_first_bin(t_vars *vars, const char *to_find, const char *str, unsigned int len)
{
	char			*ret;

	ret = NULL;
	if (!(ret = new_auto_completion_bin(vars, to_find, str)))
	{
		if (!ft_strncmp(to_find, ".", 2) || !ft_strncmp(to_find, "..", 3))
		{
			if (!(ret = ft_strjoin(to_find, "/")))
				ERROR_MEM
		}
		else if (!ft_strchr(to_find, '/'))
			ret = search_dirs_first_arg(".", to_find, len);
		else
			ret = search_dirs_and_exe(to_find);
	}
	return (ret);
}

static int			format_finding_and_get_correct_ret(char **ret, int start_actual_word, char *input, unsigned int len)
{
	char			*save;
	char			*tmp;

	save = NULL;
	tmp = NULL;
	if (!(save = ft_strndup(input, start_actual_word)))
		ERROR_MEM
	if (!(*ret))
	{
		if (!((*ret) = ft_strndup(input, len)))
			ERROR_MEM
	}
	else
	{
		if (save)
		{
			if (!(tmp = ft_strjoin(save,(*ret))))
				ERROR_MEM
			ft_strdel(ret);
		}
		if (!((*ret) = ft_strdup(tmp)))
			ERROR_MEM
		ft_strdel(&tmp);
	}
	ft_strdel(&save);
	return (0);
}

char				*new_auto_completion(char *input, unsigned int len, t_vars *vars)
{
	char			*to_find_full;
	char			*ret;
	char			*tmp;
	char			*str;
	int				start_actual_word;
	int				i;

	i = 0;

/*
	while (vars && vars->shell_vars && vars->shell_vars[i])
	{
		ft_putendl(vars->shell_vars[i++]);
usleep(100);
	}
	sleep(8);
*/
	//++ handler DOLLAR
	ret = NULL;
	tmp = NULL;
	if (!input)
		return (NULL);
	start_actual_word = get_needed_values(input, len, &str, &to_find_full);
	if (is_first_arg_and_exec(input, len, start_actual_word) == 3)
		ret = handle_first_bin(vars, to_find_full + start_actual_word, str + start_actual_word, len);
	else if (is_first_arg_and_exec(input, len, start_actual_word) == 2)
		new_auto_completion_space(vars);
	else if (is_first_arg_and_exec(input, len, start_actual_word))
		ret = handle_first_arg_dot_tilde(is_first_arg_and_exec(input, len, start_actual_word), to_find_full + start_actual_word);
	else if (!is_first_arg_and_exec(input, len, start_actual_word))
		ret = handle_x_arg(to_find_full + start_actual_word, str + start_actual_word);
	format_finding_and_get_correct_ret(&ret, start_actual_word, input, len);
	ft_strdel(&to_find_full);
	ft_strdel(&str);
	return (ret);
}
