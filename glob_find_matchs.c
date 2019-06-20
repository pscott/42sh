#include "cmd_parsing.h"

int		matchhere(char *r, char *t);

int		matchstar(int c, char *regexp, char *text)
{
	if (*text == '\0')
		return (1);
	while (*text != '\0' && (*text == c || c == '?'))
	{
		if (matchhere(regexp, text))
			return (1);
		text++;
	}
	return (0);
}

int		matchhere(char *r, char *t)
{
	if (r[0] == '\0')
		return (1);
	if (r[1] == '*')
		return (matchstar(r[0], r + 2, t));
	if (*t != '\0' && (r[0] == '?' || r[0] == *t))
		return (matchhere(r + 1, t + 1));
	//case brace
	return (0);
}

int		match(char *regexp, char *text)
{
	while (*text != '\0')
	{
		ft_dprintf(2, "|%c|", *text);
		if (matchhere(regexp, text))
			return (1);
		text++;
	}
	return (0);
}

int		find_matchs(t_st_dir *st_dir, t_st_glob *st_glob, char *str)
{
	char	*regexp;
	char	*text;

	regexp = ft_strdup(st_dir->to_find);
	text = ft_strdup(st_dir->current->d_name);
	if (match(regexp, text))
		ft_dprintf(2, "et c'est le match : %s\n", st_dir->current->d_name);
	return (0);
}
