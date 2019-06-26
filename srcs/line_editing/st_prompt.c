#include "env.h"
#include <limits.h>
#include "line_editing.h"

static char	*add_brackets(char *str)
{
	char	*res;
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	if (!(res = ft_strjoin("[", str)))
		clean_exit(1, MALLOC_ERR);
	if (!(res = ft_strjoin_free_left(res, "]")))
		clean_exit(1, MALLOC_ERR);
	return (res);
}

static char	*exit_to_str(int exit)
{
	char 	*res;
	char	*tmp;

	res = NULL;
	if (exit)
	{
		if (!(res = ft_itoa(exit)))
			clean_exit(1, MALLOC_ERR);
		tmp = res;
		res = add_brackets(res);
		ft_strdel(&tmp);
	}
	else
		if (!(res = ft_strdup("")))
			clean_exit(1, MALLOC_ERR);
	return (res);
}

static char	*dir_to_str(const char *tmp)
{
	char 	*res;
	char	*dir;
	char	buf[PATH_MAX];
	t_vars	*vars;

	if (!tmp)
		return (NULL);
	if (!(vars = get_vars(NULL)))
		return (NULL);
	if (!(dir = get_envline_value("PWD", vars->env_vars)))
		dir = getcwd(buf, PATH_MAX);
	if (!dir || (!(dir = ft_strrchr(dir, '/')) || (!*dir)))
	{
		if (!(tmp = ft_strdup("...")))
			clean_exit(1, MALLOC_ERR);
		res = add_brackets(dir);
	}
	else
	{
		dir = dir[1] ? &dir[1] : dir;
		res = add_brackets(dir);
	}
	return (res);
}

/*
**	Returns a freshly allocated st_prompt with an allocated copy of the prompt
**	parameter. If paramter is empty, duplicates the STD_PROMPT macro.
*/

t_st_prompt	*init_st_prompt(const char *name, const char *dir,
		int exit)
{
	t_st_prompt	*st_prompt;

	if (!(st_prompt = (t_st_prompt*)malloc(sizeof(*st_prompt))))
		clean_exit(1, MALLOC_ERR);
	if (!(st_prompt->name = ft_strdup(name)))
		clean_exit(1, MALLOC_ERR);
	st_prompt->dir = dir_to_str(dir);
	st_prompt->exit = exit_to_str(exit);
	if (!(st_prompt->end = ft_strdup(" $ ")))
		clean_exit(1, MALLOC_ERR);
	st_prompt->size = ft_strlen(st_prompt->name)
		+ ft_strlen(st_prompt->dir)
		+ ft_strlen(st_prompt->exit)
		+ ft_strlen(st_prompt->end);
	return (st_prompt);
}

/*
**	Memdels st_prompt and frees up the allocated memory
*/

void		free_st_prompt(t_st_prompt **st_prompt)
{
	if (!st_prompt || !(*st_prompt))
		return ;
	ft_strdel(&(*st_prompt)->name);
	ft_strdel(&(*st_prompt)->dir);
	ft_strdel(&(*st_prompt)->exit);
	ft_strdel(&(*st_prompt)->end);
	ft_memdel((void*)st_prompt);
}
