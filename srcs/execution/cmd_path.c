#include "ftsh.h"
#include "env.h"
#include "errors.h"

/*
**	Checks access for the corresponding file.
**	Returns ERR_CMD is file is NULL
**	Returns ERR_NOEXIST if file does not exist
**	Returns ERR_PERM if file exists but not executable
*/

int					check_access(const char *file)
{
	if (!file)
		return (ERR_CMD);
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == 0)
			return (0);
		return (ERR_PERM);
	}
	return (ERR_NOEXIST);
}

/*
**	For each paths in paths, tries to append file and check if the new path is
**	accessible.
**	Returns a freshly allocated string of the corresponding path, else returns
**	NULL.
*/

char				*find_path(char *file, char **paths)
{
	unsigned int	i;
	char			*possible_path;
	char			*path_w_slash;

	if (!ft_strncmp(".", file, 2) || !ft_strncmp("..", file, 3) || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (!(path_w_slash = ft_strjoin(paths[i], "/")))
			ERROR_MEM;
		if (!(possible_path = ft_strjoin(path_w_slash, file)))
			ERROR_MEM;
		ft_strdel(&path_w_slash);
		if (check_access(possible_path) == 0)
			return (possible_path);
		ft_strdel(&possible_path);
		i++;
	}
	return (NULL);
}

/*
**	Utility function to print the correpsonding error messages for
*/

static void			print_error_message(int access, const char *str)
{
	if (access == ERR_CMD)
		print_errors(ERR_CMD, ERR_CMD_STR, str);
	else if (access == ERR_NOEXIST)
		print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, str);
	else if (access == ERR_PERM)
		print_errors(ERR_PERM, ERR_PERM_STR, str);
}

/*
**	Returns a freshly allocated string containing the path corresponding
**	to the string parameter. If no path is found in the PATH variable, or the
**	file is not accessible, or not executable, returns NULL.
**	Verbose parameter prints error messages.
*/

char				*get_cmd_path(char *str, char **env, int verbose)
{
	char			**paths;
	char			*path_line;
	char			*path;
	int				access;

	ft_initialize_str(&path_line, &path, NULL, NULL);
	paths = NULL;
	if (!ft_strchr(str, '/') || !(path_line = get_envline_value("PATH", env)))
	{
		if (!(path = ft_strdup(str)))
			ERROR_MEM;
	}
	else if (!(paths = ft_strsplit(path_line, ":")))
		ERROR_MEM;
	if (!path && !(path = find_path(str, paths)))
		;
	ft_free_ntab(paths);
	access = check_access(path);
	if (access == 0)
		return (path);
	else if (verbose)
		print_error_message(access, str);
	return (NULL);
}
