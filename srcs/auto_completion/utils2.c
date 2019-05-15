#include "libft.h"
#include "line_editing.h"

int				is_same_char(char a, char b)
{
	if (a == b)
		return (1);
	if (a <= 'Z' && a >= 'A' && a + 32 == b)
		return (1);
	if (a <= 'z' && a >= 'a' && a - 32 == b)
		return (1);
	return (0);
}

int				get_needed_values(char *input, unsigned int len, char **str
					, char **to_find_full)
{
	int			start_actual_word;

	start_actual_word = len;
	*str = NULL;
	*to_find_full = NULL;
	if (!(*str = ft_strndup(input, len + 1)))
		ERROR_MEM
	if (!(*to_find_full = ft_strndup(input, len)))
		ERROR_MEM
	if (len > 0 && is_white_spaces((*to_find_full)[len - 1]))
		start_actual_word--;
	while (start_actual_word > 0 && !is_white_spaces((*to_find_full)[start_actual_word]))
		start_actual_word--;
	if (is_white_spaces((*to_find_full)[start_actual_word]))
		start_actual_word++;
	return (start_actual_word);
}

int				get_path(char ***path, t_vars *vars)
{
	char		*tmpath;

	if (!vars || !vars->env_vars)
		return (0);
	if (!(tmpath = get_envline_value("PATH", vars->env_vars)))
	{
		*path = NULL;
		return (0);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		ERROR_MEM
	return (0);
}
