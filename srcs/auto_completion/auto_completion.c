#include "libft.h"
#include "errors.h"
#include "line_editing.h"

static int			get_path(char ***path, t_vars *vars)
{
	char			*tmpath;

	if (!vars || !vars->env_vars)
		return (0);
	if (!(tmpath = get_envline_value("PATH", vars->env_vars)))
	{
		*path = NULL;
		return (0);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		return (ERR_MALLOC);
	return (0);
}

static int			new_check_lst_args(char *str)
{
	int				i;

	i = 0;
	while ((str[i]) && is_white_spaces(str[i]))
		i++;
	while (str[i] && !is_white_spaces(str[i]))
		i++;
	if (str && is_white_spaces(str[i]))
		return (0);
	return (1);
}

static int			new_check_first_arg(char *str)
{
	int				i;

	i = 0;
	while (str[i + 1] && is_white_spaces(str[i]))
		i++;
	if (str && (str[i] == '/' || str[i] == '.' || str[i] == '~'))
		return (1);
	return (0);
}

static char			*new_auto_completion_bin(char *str, unsigned int len, t_vars *vars)
{
	char			**path;
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;
	int				i;

	match = NULL;
	ret_str = NULL;
	i = -1;
	path = NULL;
	if (get_path(&path, vars))//recup le path
		return (NULL);
//		return (ERR_MALLOC);
	if (!(to_find = ft_strdup(str)))
		return (NULL);
//		return (ERR_MALLOC);
	//ft_putchar('\n');
	if (find_matching_exe(path, &match, to_find, 1))//stock dans match les noms correspondants
	{
		ft_free_ntab(path);
		//ERR_MALLOC
		return (NULL);
	}
	ft_free_ntab(path);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, len);
	ft_strdel(&to_find);
	return (ret_str);
}

static int			new_auto_completion_file(char *str, unsigned int len)
{
/*	char			*to_find;
	char			*path_file;
	t_auto_comp		*match;

	match = NULL;
	if (!(to_find = get_to_find_file(str)))
		return (ERR_MALLOC);
	if (!(path_file = get_path_file(str, &to_find)))
	{
		ft_strdel(&to_find);
		return (ERR_MALLOC);
	}
	if (find_matching_exe(&path_file, &match, to_find, 0))	
	{
		ft_strdel(&to_find);
		ft_strdel(&path_file);
		return (ERR_MALLOC);
	}
	if (!to_find)
		if (!(to_find = ft_strnew(1)))
		{
			ft_strdel(&to_find);
			ft_strdel(&path_file);
			return (ERR_MALLOC);
		}
	if (match)
		get_ret_or_display_matches(match, to_find, len);
	ft_strdel(&path_file);
	ft_strdel(&to_find);*/
	return (0);
}

char				*new_auto_completion(char *input, unsigned int len, t_vars *vars)// len +1
{
	char			*str;
	char			*ret;
//vars->env = **environment;
	if (!input)
		return (NULL);
	if (!(str = ft_strndup(input, len)))
		return (NULL);//MALLOC ERR
	ret = NULL;
//	ft_putchar('|');
//	ft_putendl(str);
	if (new_check_lst_args(str) && !new_check_first_arg(str))
	{
		if (!(ret = new_auto_completion_bin(str, len, vars)))
			return (NULL);
			//return (ERR_MALLOC);
	}
/*	else
	{
		if (new_auto_completion_file(str, len))
			return (ERR_MALLOC);
	}
*/	ft_strdel(&str);
//	sleep(1);
	return (ret);
}
