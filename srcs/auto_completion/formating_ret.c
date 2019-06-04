#include "auto_completion.h"

int		format_finding_and_get_correct_ret(char **ret,
		int start_actual_word, char *input, unsigned int len)
{
	char	*save;
	char	*tmp;

	initialize_str(&save, &tmp, NULL, NULL);
	if (!(save = ft_strndup(input, start_actual_word)))
		ERROR_MEM;
	if (!(*ret))
	{
		if (!(*ret = ft_strndup(input, len)))
			ERROR_MEM;
	}
	else
	{
		if (save)
		{
			if (!(tmp = ft_strjoin(save, (*ret))))
				ERROR_MEM;
			ft_strdel(ret);
		}
		if (!((*ret) = ft_strdup(tmp)))
			ERROR_MEM;
		ft_strdel(&tmp);
	}
	ft_strdel(&save);
	return (0);
}
