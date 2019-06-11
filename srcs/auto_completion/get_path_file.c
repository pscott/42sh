#include "auto_completion.h"

static int			get_path_user(int index, const char *arg, char **path,
					char **to_find)
{
	char			*home;
	char			*tmp;
	char			*tmp2;

	if (!getenv("HOME"))
	{
		if (!(home = ft_strdup("/Users")))
			clean_exit(1, 1);
	}
	else
	{
		if (!(home = ft_strdup(getenv("HOME"))))
			clean_exit(1, 1);
	}
	tmp = ft_strsub(arg, index + 1, ft_strlen(arg) - index);
	tmp2 = ft_strsub(arg, 1, index);
	*to_find = tmp;
	if (!(*path = ft_strjoin(home, tmp2)))
		clean_exit(1, 1);
	ft_strdel(&tmp2);
	ft_strdel(&home);
	return (0);
}

static int			get_path_root(int index, const char *arg, char **path,
					char **to_find)
{
	char			*tmp;

	tmp = NULL;
	if (arg[index + 1])
	{
		if (!(*to_find = ft_strsub(arg, index + 1, ft_strlen(arg) - index)))
			clean_exit(1, 1);
		if (!(*path = ft_strsub((arg), 0, index + 1)))
			clean_exit(1, 1);
	}
	else
	{
		if (!(*path = ft_strdup(arg)))
			clean_exit(1, 1);
		if (!(*to_find = ft_strnew(0)))
			clean_exit(1, 1);
	}
	return (0);
}

static int			get_root(const char *arg, char **path, char **to_find)
{
	int				len;

	if ((arg)[1])
	{
		len = ft_strlen(arg) - 1;
		if (!(*to_find = ft_strsub(arg, 1, len)))
			clean_exit(1, 1);
	}
	else if (!(*to_find = ft_strnew(0)))
		clean_exit(1, 1);
	if (!(*path = ft_strdup("/")))
		clean_exit(1, 1);
	return (0);
}

static int			get_path_reg(int index, const char *arg, char **path,
					char **to_find)
{
	char			*tmp_path;
	char			*pwd_slash;
	char			*pwd;

	initialize_str(&tmp_path, &pwd_slash, &pwd, NULL);
	get_pwd_and_pwd_slash(&pwd, &pwd_slash);
	if (!ft_strchr(arg, '/'))
	{
		if (!((*path) = ft_strdup(pwd_slash)))
			clean_exit(1, 1);
		if (!(*to_find = ft_strdup(arg)))
			clean_exit(1, 1);
	}
	else
	{
		if (!(*to_find = ft_strsub(arg, index + 1, ft_strlen(arg) - index)))
			clean_exit(1, 1);
		tmp_path = ft_strsub(arg, 0, index + 1);
		if (!(*path = ft_strjoin(pwd_slash, tmp_path)))
			clean_exit(1, 1);
		ft_strdel(&tmp_path);
	}
	free_two_strings(&pwd_slash, &pwd);
	return (0);
}

int					get_path_file_and_to_find(const char *arg, char **path,
					char **to_find)
{
	char			*pwd;
	int				i;

	initialize_str(&pwd, &pwd, path, NULL);
	i = ft_strlen(arg) - ft_strlen(ft_strrchr(arg, '/'));
	if ((arg)[0] == '~' && (arg)[1] == '/')
		get_path_user(i, arg, path, to_find);
	else if (arg[0] && !i)
		get_root(arg, path, to_find);
	else if ((arg)[0] == '/' && i > 0)
		get_path_root(i, arg, path, to_find);
	else if ((arg)[0] != '/' && i > 0)
		get_path_reg(i, arg, path, to_find);
	else
	{
		if (!(pwd = getcwd(pwd, PATH_MAX)))
			return (1);
		else if (!(*path = ft_strdup(pwd)))
			clean_exit(1, 1);
		if (!(*to_find = ft_strnew(0)))
			clean_exit(1, 1);
		ft_strdel(&pwd);
	}
	return (0);
}
