#include "auto_completion.h"

static int		get_filename(const char *next, const char *to_find,
		const char *key, char **filename)
{
	if (ft_strlen(next) == ft_strlen(to_find)
			|| ft_is_white_space(next[ft_strlen(to_find)]))
	{
		if (!(*filename = ft_strjoin(key, " ")))
			clean_exit(1, 1);
	}
	else if (!(*filename = ft_strdup(key)))
		clean_exit(1, 1);
	return (0);
}

static int		check_vars(char **path, t_auto_comp **match,
		const char *to_find, const char *next)
{
	char			*filename;
	char			*key;
	int				i;

	filename = NULL;
	i = 0;
	while (path[i])
	{
		if (!(key = ft_strndup(path[i], ft_strlen_char(path[i], '='))))
			clean_exit(1, 1);
		if (ft_strnequ(key, to_find, ft_strlen(to_find)))
		{
			get_filename(next, to_find, key, &filename);
			create_match_link(match, filename);
			ft_strdel(&filename);
		}
		ft_strdel(&key);
		i++;
	}
	return (0);
}

static int		get_matching_varz(t_vars *vars, t_auto_comp **match,
		const char *to_find_real, const char *next)
{
	*match = NULL;
	if (vars->shell_vars)
		check_vars(vars->shell_vars, match, to_find_real, next);
	if (!(*match))
		return (0);
	return (0);
}

static char			*get_final_ret(char **ret_str, char **tmp, char *next, int mode)
{
	int				space;
	char			tmp_1;

	space = 0;
	if (!next[ft_strlen(next) - 1] || ft_is_white_space(next[ft_strlen(next) - 1]))
		space = 1;
	if (mode == 1 && space == 1)
	{
		if (!(tmp_1 = ft_strjoin(*tmp, " ")))
			clean_exit(1, 1);
	}
	if (mode == 2 && space == 0)
	{
		if (!(tmp_1 = ft_strjoin(*tmp, "}")))
			clean_exit(1, 1);
	}
	if (mode == 2 && space == 1)
	{
		if (!(tmp_1 = ft_strjoin(*tmp, "} ")))
			clean_exit(1, 1);
	}

}

static char			*get_ret(char **ret_str, char **to_find, char *next, int mode)
{
	char			*tmp;
	char			prefix[4];
	int				i;

	i = 0;
	while (i < 3)
		prefix[i++] = 0;
ft_dprintf(2, "\nto_f |%s|\n", *to_find);
	prefix[0] = '$';
	if (mode == 2)
		prefix[1] = '{';
	if (!(tmp = ft_strjoin(prefix, *ret_str)))
		clean_exit(1, 1);
	ft_strdel(ret_str);
	ft_strdel(to_find);
	get_final_ret(ret_str, &tmp, next, mode);
	
	return (tmp);
}

char				*varz(const char *str, const char *next)
{
	t_vars			*vars;
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;
	int				i;

	vars = get_vars(NULL);
	i = 1;
	if (str && str[1] == '{')
		i++;
	if (!(to_find = ft_strdup(str + i)))
		clean_exit(1, 1);
	get_matching_varz(vars, &match, to_find, next);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find,
				ft_strlen(to_find));
	else
		ret_str = NULL;
	ft_dprintf(2, "\nret str{{%s}}\n", ret_str);
	return (get_ret(&ret_str, &to_find, next, i));;
}
