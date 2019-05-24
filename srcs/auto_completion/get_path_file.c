#include "libft.h"
#include "line_editing.h"

static int			get_path_user(int index, const char *arg, char **path, char **to_find)
{
	char			*home;
	char			*tmp;
	char			*tmp2;

	if (!getenv("HOME"))
	{
		if (!(home = ft_strdup("/Users")))
			ERROR_MEM
	}
	else
	{
		if (!(home = ft_strdup(getenv("HOME"))))
			ERROR_MEM
	}
	tmp = ft_strsub(arg, index + 1, ft_strlen(arg) - index);
	tmp2 = ft_strsub(arg, 1, index);
	*to_find = tmp;
	if (!(*path = ft_strjoin(home, tmp2)))
		ERROR_MEM
	ft_strdel(&tmp2);
	ft_strdel(&home);
	return (0);
}

static int			get_path_root(int index, const char *arg, char **path, char **to_find)
{
	char			*tmp;

	tmp = NULL;
	if (arg[index + 1])
	{
		if (!(*to_find = ft_strsub(arg, index + 1, ft_strlen(arg) - index)))
			ERROR_MEM
		if (!(*path = ft_strsub((arg), 0, index + 1)))
			ERROR_MEM
	}
	else
	{
		if (!(*path = ft_strdup(arg)))
			ERROR_MEM
		if (!(*to_find = ft_strnew(0)))
			ERROR_MEM
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
			ERROR_MEM
	}
	else
		if (!(*to_find = ft_strnew(0)))
			ERROR_MEM
	if (!(*path = ft_strdup("/")))
		ERROR_MEM
	return (0);
}

static int			get_path_reg(int index, const char *arg, char **path, char **to_find)
{
	char			*tmp_path;
	char			*pwd_slash;
	char			*pwd;

	tmp_path = NULL;
	pwd_slash = NULL;
	pwd = NULL;
	if (!(pwd = getcwd(pwd, PATH_MAX)))
		ERROR_MEM
	if (!(pwd_slash = ft_strjoin(pwd, "/")))
		ERROR_MEM
	if (!ft_strchr(arg, '/'))
	{
		if (!((*path) = ft_strdup(pwd_slash)))
			ERROR_MEM
		if (!(*to_find = ft_strdup(arg)))
			ERROR_MEM
	}
	else
	{	
		if (!(*to_find = ft_strsub(arg, index + 1, ft_strlen(arg) - index)))
			ERROR_MEM
		tmp_path = ft_strsub(arg, 0, index + 1);
		if (!(*path = ft_strjoin(pwd_slash, tmp_path)))
			ERROR_MEM
		ft_strdel(&tmp_path);
	}
	free_two_strings(&pwd_slash, &pwd);
	return (0);
}

int					get_path_file_and_to_find(const char *arg, char **path, char **to_find)
{
	char			*pwd;
	int				i;

	pwd = NULL;
	*path = NULL;
	i = 0;
	if (!(pwd = getcwd(pwd, PATH_MAX)))
		ERROR_MEM
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
		if (!(*path = ft_strdup(pwd)))
			ERROR_MEM
		if (!(*to_find = ft_strnew(0)))
			ERROR_MEM
	}
	ft_strdel(&pwd);
	return (0);
}
