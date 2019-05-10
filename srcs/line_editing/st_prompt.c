#include "line_editing.h"
#include "ast.h"

/*
**	Returns a freshly allocated st_prompt with an allocated copy of the prompt
**	parameter. If paramter is empty, duplicates the STD_PROMPT macro.
*/

t_st_prompt	*init_st_prompt(const char *prompt)
{
	t_st_prompt	*st_prompt;

	if (!(st_prompt = (t_st_prompt*)malloc(sizeof(*st_prompt))))
		ERROR_MEM;
	if (!prompt)
	{
		if (!(st_prompt->prompt = ft_strdup(STD_PROMPT)))
			ERROR_MEM;
	}
	else
		st_prompt->prompt = ft_strdup(prompt);
	st_prompt->size = ft_strlen(st_prompt->prompt);
	return (st_prompt);
}
