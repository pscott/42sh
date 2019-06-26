#include "auto_completion.h"

static char			*get_name(const char *to_find,
						const char *next, char *type)
{
	char		*filename;

	if (ft_strlen(next) == ft_strlen(to_find)
			|| ft_is_white_space(next[ft_strlen(to_find)]))
	{
		if (!(filename = ft_strjoin(type, " ")))
			clean_exit(1, MALLOC_ERR);
	}
	else if (!(filename = ft_strdup(type)))
		clean_exit(1, MALLOC_ERR);
	return (filename);
}

static int			add_other_builtins_2(t_auto_comp **match,
					const char *to_find, const char *next, int mode)
{
	char			*tmp;

	tmp = NULL;
	if (mode == 0 || !compare_entry(to_find, "type"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "type"))));
	}
	if (mode == 0 || !compare_entry(to_find, "fg"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "fg"))));
	}
	if (mode == 0 || !compare_entry(to_find, "cd"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "cd"))));
	}
	if (mode == 0 || !compare_entry(to_find, "hash"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "hash"))));
	}
	ft_strdel(&tmp);
	return (0);
}

static int			add_other_builtins(t_auto_comp **match, const char *to_find,
					const char *next, int mode)
{
	char			*tmp;

	tmp = NULL;
	if (mode == 0 || !compare_entry(to_find, "set"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "set"))));
	}
	if (mode == 0 || !compare_entry(to_find, "jobs"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "jobs"))));
	}
	if (mode == 0 || !compare_entry(to_find, "bg"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "bg"))));
	}
	if (mode == 0 || !compare_entry(to_find, "unset"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "unset"))));
	}
	ft_strdel(&tmp);
	return (add_other_builtins_2(match, to_find, next, mode));
}

int					add_builtins(t_auto_comp **match, const char *to_find,
					const char *next, int mode)
{
	char			*tmp;

	tmp = NULL;
	if (mode == 0 || !compare_entry(to_find, "exit"))
		create_match_link(match, ((tmp = get_name(to_find, next, "exit"))));
	if (mode == 0 || !compare_entry(to_find, "echo"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "echo"))));
	}
	if (mode == 0 || !compare_entry(to_find, "export"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "export"))));
	}
	if (mode == 0 || !compare_entry(to_find, "fc"))
	{
		ft_strdel(&tmp);
		create_match_link(match, ((tmp = get_name(to_find, next, "fc"))));
	}
	ft_strdel(&tmp);
	add_other_builtins(match, to_find, next, mode);
	return (0);
}
