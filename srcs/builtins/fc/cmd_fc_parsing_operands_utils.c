#include "ftsh.h"
#include "history.h"
#include "auto_completion.h"

int				parse_case_s_fc(t_st_fc *st_fc, char **argv, int i)
{
	int			len;

	if (argv[i] && ft_strchr(argv[i], '='))
	{
		len = ft_strlen_char(argv[i], '=');
		if (!(st_fc->old_pattern = ft_strndup(argv[i], len)))
			clean_exit(1, MALLOC_ERR);
		if (!(st_fc->new_pattern = ft_strdup(argv[i] + len + 1)))
			clean_exit(1, MALLOC_ERR);
		if (argv[i + 1])
		{
			if (!(st_fc->first = ft_strdup(argv[i + 1])))
				clean_exit(1, MALLOC_ERR);
		}
	}
	else if (argv[i])
		if (!(st_fc->first = ft_strdup(argv[i])))
			clean_exit(1, MALLOC_ERR);
	return (0);
}

int				get_first_and_last(t_st_fc *st_fc, char **argv, int i)
{
	if (!argv[i])
		return (1);
	if (!(st_fc->first))
	{
		if (!(st_fc->first = ft_strdup(argv[i])))
			clean_exit(1, MALLOC_ERR);
		i++;
	}
	if (argv[i] && !(st_fc->last) && (st_fc->first))
	{
		if (!(st_fc->last = ft_strdup(argv[i])))
			clean_exit(1, MALLOC_ERR);
	}
	return (0);
}
