#include "libft.h"
#include "line_editing.h"

static char			*get_path_user(int index, char **find)
{
	char			*home;
	char			*tmp;
	char			*tmp2;
	char			*ret;

	ret = NULL;
	if (!getenv("HOME"))
	{
		if (!(home = ft_strdup("/Users")))
			return (NULL);
	}
	else
	{
		if (!(home = ft_strdup(getenv("HOME"))))
			return (NULL);
	}
	tmp = ft_strsub(*find, index + 1, ft_strlen(*find) - index);
	tmp2 = ft_strsub(*find, 1, index);
	ft_strdel(find);
	*find = tmp;
	ret = ft_strjoin(home, tmp2);
	ft_strdel(&tmp2);
	ft_strdel(&home);
//	ft_putendl(ret);
	return (ret);
}

static char			*get_path_root(int index, char **find)
{
	char			*tmp;
	char			*ret;

	if ((*find)[index + 1])
	{
		tmp = ft_strsub((*find), index + 1, ft_strlen(*find) - index);
		ret = ft_strsub((*find), 0, index + 1);
		ft_strdel(find);
		(*find) = tmp;
	}
	else
	{
		if (!(ret = ft_strdup(*find)))
			return (NULL);
		ft_strdel(find);
		if (!(*find = ft_strnew(0)))
		{
			ft_strdel(&ret);
			return (NULL);
		}
	}
	return (ret);
}

static char			*get_root(char **find)
{
	int				len;
	char			*ret;
	char			*tmp;

	ret = NULL;
	tmp = NULL;
	if ((*find)[1])
	{
		len = ft_strlen(*find) - 1;
		tmp = ft_strsub(*find, 1, len);
		ft_strdel(find);
		(*find) = tmp;
	}
	else
		ft_strdel(find);
	if (!(ret = ft_strdup("/")))
		ft_strdel(&tmp);
	return (ret);
}

static char			*get_path_reg(int index, char *pwd, char **find)
{
	char			*tmp_find;
	char			*tmp_ret;
	char			*ret;
	char			*pwd_slash;

	tmp_find = NULL;
	tmp_ret = NULL;
	pwd_slash = NULL;
	ret = NULL;
	tmp_find = ft_strsub(*find, index + 1, ft_strlen(*find) - index);
	tmp_ret = ft_strsub(*find, 0, index + 1);
	if (!(pwd_slash = ft_strjoin(pwd, "/")))
		ERROR_MEM
	if (!(ret = ft_strjoin(pwd_slash, tmp_ret)))
		ERROR_MEM
	ft_strdel(&tmp_ret);
	ft_strdel(&pwd_slash);
	ft_strdel(find);
	*find = tmp_find;
	return (ret);
}

char				*get_path_file(char **find)
{
	char			*pwd;
	char			*ret;
	int				i;

	pwd = NULL;
	ret = NULL;
	i = 0;
	if (!(pwd = getcwd(pwd, PATH_MAX)))
		return (NULL);
	i = ft_strlen(*find) - ft_strlen(ft_strrchr(*find, '/'));
	if ((*find)[0] == '~' && (*find)[1] == '/')
		ret = get_path_user(i, find);
	else if (!i)
		ret = get_root(find);
	else if ((*find)[0] == '/' && i > 0)
		ret = get_path_root(i, find);
	else if ((*find)[0] != '/' && i > 0)
		ret = get_path_reg(i, pwd, find);
	else
		ret = ft_strdup(pwd);
	ft_strdel(&pwd);
	return (ret);
}
