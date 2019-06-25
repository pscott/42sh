#include "auto_completion.h"
#include "cmd_parsing.h"

int		format_finding_and_get_correct_ret(char **ret,
		int start_actual_word, char *input, unsigned int len)
{
	char		*save;
	char		*tmp;

	initialize_str(&save, &tmp, NULL, NULL);
	if (!(save = ft_strndup(input, start_actual_word)))
		clean_exit(1, MALLOC_ERR);
	if (!(*ret))
	{
		if (!(*ret = ft_strndup(input, len)))
			clean_exit(1, MALLOC_ERR);
	}
	else
	{
		if (save)
		{
			if (!(tmp = ft_strjoin(save, (*ret))))
				clean_exit(1, MALLOC_ERR);
			ft_strdel(ret);
		}
		if (!((*ret) = ft_strdup(tmp)))
			clean_exit(1, MALLOC_ERR);
		ft_strdel(&tmp);
	}
	ft_strdel(&save);
	return (0);
}
