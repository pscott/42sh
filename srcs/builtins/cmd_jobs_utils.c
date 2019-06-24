#include "jobs.h"

static t_job_opt	parse_options(char *str)
{
	int			j;
	t_job_opt	opt;

	j = 1;
	opt = DEFAULT;
	while (str[j])
	{
		if (str[j] == 'p')
			opt = PID;
		else if (str[j] == 'l')
			opt = LONG;
		else if (str[j] == 0)
			break ;
		else
			return (ERROR);
		j++;
	}
	return (opt);
}

int					get_options(char **argv, int *i)
{
	t_job_opt	opt;

	opt = DEFAULT;
	while (argv[*i])
	{
		if (argv[*i][0] == '-')
		{
			if (argv[*i][1] == '-')
				return (opt);
			else if (!argv[*i][1])
				return (opt);
			if ((opt = parse_options(argv[*i])) == ERROR)
				return (ERROR);
		}
		else
			return (opt);
		(*i)++;
	}
	return (opt);
}
