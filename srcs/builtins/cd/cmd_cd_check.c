#include "builtins.h"
#include <sys/stat.h>
#include "errors.h"

static void		remove_string_dotdot(char **dest, int *i)
{
	if (*i == 0 && (*dest)[*i] == '/')
		(*i)++;
	*dest = remove_n_char(*dest, *i);
	*dest = remove_n_char(*dest, *i);
	*dest = remove_n_char(*dest, *i);
	if (*i == 1)
		(*i)--;
	while (*i >= 1)
	{
		*dest = remove_n_char(*dest, *i);
		(*i)--;
		if ((*dest)[*i] == '/')
			break ;
	}
}

static int		is_error(char *dest, char *msg)
{
	struct stat		infos;
	char			*ptr;

	if (!ft_strcmp(msg, "-"))
		ptr = dest;
	else
		ptr = msg;
	if (!dest)
		return (1);
	if (stat(dest, &infos) == -1)
		return (print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, ptr));
	else if (!S_ISDIR(infos.st_mode))
		return (print_errors(ERR_NOTDIR, ERR_NOTDIR_STR, ptr));
	else if (access(dest, F_OK) == 0 && access(dest, X_OK) == -1)
		return (print_errors(ERR_PERM, ERR_PERM_STR, ptr));
	else
		return (0);
}

static int		loop_access(char *dest, char *msg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (dest[0] && dest[i] && (ft_strncmp(dest + i, "/../", 4)
				&& ft_strcmp(dest + i, "/..")))
	{
		i++;
		while (dest[i] && dest[i] != '/')
			i++;
		i++;
		if (!(tmp = ft_strndup(dest, i)))
			clean_exit(1, 1);
		if (is_error(tmp, msg))
		{
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
		i--;
	}
	return (0);
}

static int		access_last_part(char **dest, char *msg, int i)
{
	if (!ft_strncmp(*dest + i, "/../", 4)
			|| !ft_strcmp(*dest + i, "/.."))
		remove_string_dotdot(dest, &i);
	if (is_error(*dest, msg))
		return (1);
	return (0);
}

int				check_full_access(char **dest, char *msg)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while ((*dest)[i])
	{
		while ((*dest)[i] && (*dest)[i] != '/')
			i++;
		if (!ft_strncmp(*dest + i, "/../", 4)
				|| !ft_strcmp(*dest + i, "/.."))
		{
			remove_string_dotdot(dest, &i);
			i = 0;
		}
		else if ((*dest)[i])
			i++;
		if (loop_access(*dest, msg))
			return (1);
	}
	while (i > 0 && (*dest)[i] != '/')
		i--;
	return (access_last_part(dest, msg, i));
}
