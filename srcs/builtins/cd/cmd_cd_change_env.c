#include "builtins.h"
#include "env.h"
#include "errors.h"

/*
**	Handle L flag and no flag situations
*/

static int		handle_no_p(char *new_wd, char ***env, char **pwd)
{
	char	*tmp;

	if (new_wd[0] == '/')
	{
		if (!((*pwd) = ft_strdup(new_wd)))
			clean_exit(1, MALLOC_ERR);
	}
	else
	{
		if (((*pwd) = get_envline_value("PWD", *env)))
		{
			if (!(tmp = ft_strjoin((*pwd), "/")))
				clean_exit(1, MALLOC_ERR);
			if (!((*pwd) = ft_strjoin(tmp, new_wd)))
				clean_exit(1, MALLOC_ERR);
			ft_strdel(&tmp);
		}
		else if (!((*pwd) = getcwd(NULL, 0)))
			return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	}
	return (0);
}

/*
**	Updates the OLDPWD value
*/

static void		update_oldpwd(t_vars *vars, int display)
{
	char		*old_pwd;

	old_pwd = get_directory("PWD", vars);
	if (!old_pwd)
	{
		unset_env_var("OLDPWD", &vars->env_vars);
		unset_env_var("OLDPWD", &vars->shell_vars);
		unset_env_var("OLDPWD", &vars->env_save);
	}
	else
	{
		if (display == 2)
			ft_printf("%s\n", get_envline_value("OLDPWD", vars->env_vars));
		set_env_var("OLDPWD", old_pwd, &vars->env_vars);
		set_env_var("OLDPWD", old_pwd, &vars->shell_vars);
		set_env_var("OLDPWD", old_pwd, &vars->env_save);
		ft_strdel(&old_pwd);
	}
}

/*
**	Updates the pwd and oldpwd env variables, then calls chdir.
**	Returns 0 on success, else returns 1. Display says which message we have
**	to display (in the case that CDPATH is used, or -). 0 means nothing,
**	1 means CDPATH, 2 means '-'
*/

int				change_environ(char *new_wd, t_vars *vars, int opt, int display)
{
	char			*pwd;
	int				ret;

	pwd = NULL;
	if ((ret = chdir(new_wd)) == -1)
		print_errors(ERR_CHDIR, ERR_CHDIR_STR, new_wd);
	if (opt == 'L' || opt == 0)
	{
		if ((ret = handle_no_p(new_wd, &vars->env_vars, &pwd)))
			return (ret);
	}
	else
	{
		if (!(pwd = getcwd(NULL, 0)))
			return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	}
	update_oldpwd(vars, display);
	add_variables("PWD", pwd, &vars->env_vars);
	add_variables("PWD", pwd, &vars->shell_vars);
	add_variables("PWD", pwd, &vars->env_save);
	if (display == 1)
		ft_printf("%s\n", pwd);
	ft_strdel(&new_wd);
	ft_strdel(&pwd);
	return (ret);
}
