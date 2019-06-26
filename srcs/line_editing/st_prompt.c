#include "line_editing.h"

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
