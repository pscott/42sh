#include "jobs.h"

t_job	*current_case(char current, const char *builtin)
{
	t_job	*res;
	char	*curr_str;

	res = find_job_by_current(current);
	if (!(res))
	{
		if (!(curr_str = current == '+'
					? ft_strdup("current") : ft_strdup("last")))
			clean_exit(1, 1);
		ft_dprintf(2, SHELL_NAME ": %s: %s: no such job\n", builtin, curr_str);
		ft_strdel(&curr_str);
	}
	return (res);
}

t_job	*subcommand_case(const char *subcommand, const char *builtin)
{
	t_job	*res;
	t_job	*probe;

	res = find_job_by_subcommand(subcommand);
	if (!(res))
	{
		ft_dprintf(2, SHELL_NAME ": %s: %s: no such job\n", builtin, subcommand);
		return (NULL);
	}
	probe = res->next;
	while (probe)
	{
		if (ft_strstr(probe->command, subcommand))
		{
			ft_dprintf(2, SHELL_NAME ": %s: %s: ambiguous job spec\n",
					builtin, subcommand);
			return (NULL);
		}
		probe = probe->next;
	}
	return (res);
}

t_job	*command_case(const char *command, const char *builtin)
{
	t_job	*res;
	t_job	*probe;

	res = find_job_by_command(command);
	if (!(res))
	{
		ft_dprintf(2, SHELL_NAME ": %s: %s: no such job\n", builtin, command);
		return (NULL);
	}
	probe = res->next;
	while (probe)
	{
		if (ft_strnequ(probe->command, command, ft_strlen(command)))
		{
			ft_dprintf(2, SHELL_NAME ": %s: %s: ambiguous job spec\n",
					builtin, command);
			return (NULL);
		}
		probe = probe->next;
	}
	return (res);
}

t_job	*number_case(int num, const char *builtin)
{
	t_job	*res;

	res = find_job_by_number(num);
	if (!(res))
		ft_dprintf(2, SHELL_NAME ": %s: %d: no such job\n", builtin, num);
	return (res);
}

/*
**	Returns the corresponding job to the str parameter. Returns NULL on error
**	(multiple jobs, or no corresponding jobs).
*/

t_job	*get_job(const char *str, const char *builtin)
{
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = -1;
	if (*str == '%')
		i++;
	if (str[++i] == '%' || str[i] == '+' || str[i] == 0)
		return (current_case('+', builtin));
	else if (str[i] == '-')
		return (current_case('+', builtin));
	else if (str[i] == '?')
		return (subcommand_case(&str[i + 1], builtin));
	else if (!ft_isdigit(str[i]))
		return (command_case(&str[i], builtin));
	else
	{
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		if (str[i + j])
			return (command_case(&str[i], builtin));
		return (number_case(ft_atoi(&str[i]), builtin));
	}
}
