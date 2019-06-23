#include "auto_completion.h"
#include "cmd_parsing.h"

int		format_finding_and_get_correct_ret(char **ret,
		int start_actual_word, char *input, unsigned int len)
{
	char	*save;
	char	*tmp;
	
	char	c[2];
	size_t		i[2];

	initialize_str(&save, &tmp, NULL, NULL);

	if (*ret && input && ft_strlen(*ret) > ft_strlen(input) && start_actual_word > 0 && (c[0] = input[start_actual_word - 1]))
	{
		c[1] = '\0';
		i[0] = ft_strlen(*ret) - 1;
		i[1] = ft_strlen(*ret) - 1;
		if (start_actual_word >= 1 && ft_is_quote(input[start_actual_word - 1]))
		{
			if (c[0] == '\'')
				substitute_slice(ret, i, "\' ");
			else if (c[0] == '\"')
				substitute_slice(ret, i, "\" ");
		}
	}


	if (!(save = ft_strndup(input, start_actual_word)))
		clean_exit(1, 1);
	if (!(*ret))
	{
		if (!(*ret = ft_strndup(input, len)))
			clean_exit(1, 1);
	}
	else
	{
		if (save)
		{
			if (!(tmp = ft_strjoin(save, (*ret))))
				clean_exit(1, 1);
			ft_strdel(ret);
		}
		if (!((*ret) = ft_strdup(tmp)))
			clean_exit(1, 1);
		ft_strdel(&tmp);
	}
	ft_strdel(&save);
	return (0);
}
