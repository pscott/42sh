#include "ftsh.h"
#include "lexer.h"
#include "cmd_parsing.h"

/*
**	Utilty function for get_token_from_argv. Joins s1 and s2 in a freshly
**	allocated string, and frees s1.
*/

static char			*ft_strjoin_free(char *s1, char *s2)
{
	char			*res;
	unsigned int	s1_len;

	if (!s2)
	{
		res = ft_strdup(s1);
		ft_strdel(&s1);
		return (res);
	}
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	if (!(res = ft_strnew(s1_len + ft_strlen(s2))))
		ERROR_MEM;
	ft_strcpy(res, s1);
	ft_strcat(&res[s1_len], s2);
	ft_strdel(&s1);
	return (res);
}

/*
**	Utility function for get_argv_from_token_lst.
**	Separates words in the string, filling the argv with the different words
*/

static void			apply_ifs(const char *string, char **argv, unsigned int *i)
{
	char			**words;
	unsigned int	j;

	if (!(words = ft_strsplit(string, IFS)))
		ERROR_MEM;
	j = 0;
	while (words[j])
	{
		if (!(argv[*i] = ft_strjoin_free(argv[*i], words[j])))
			ERROR_MEM;
		j++;
		(*i)++;
	}
	if (j)
		(*i)--;
	ft_free_ntab(words);
}

/*
**	Utility function for get_argv_from_token_lst.
*/

static char			**create_argv(t_token *token_head, unsigned int argv_len)
{
	char			**argv;
	unsigned int	i;

	if (!(argv = (char**)malloc(sizeof(*argv) * (argv_len + 1))))
		ERROR_MEM;
	ft_bzero(argv, sizeof(*argv) * (argv_len + 1));
	i = 0;
	while (i < argv_len)
	{
		while (is_argv_token(token_head))
		{
			if (token_head->type == tk_word)
				apply_ifs(token_head->content, argv, &i);
			else
			{
				if (!(argv[i] = ft_strjoin_free(argv[i], token_head->content)))
					ERROR_MEM;
			}
			token_head = token_head->next;
		}
		while (token_head && token_head->type == tk_eat)
			token_head = token_head->next;
		i++;
	}
	return (argv);
}

/*
**	Utility function for get_argv_from_token_lst
**	Returns the number of words contained in the token.
**	If token is a tk_word, separates words according to IFS.
**	Else returns 1
*/
static unsigned int	token_length(t_token *probe)
{
	unsigned int	argv_len;
	char			**words;

	if (probe->type != tk_word)
		return (1);
	else
	{
		if (!(words = ft_strsplit(probe->content, IFS)))
			ERROR_MEM;
		argv_len = ft_ntab_len((const char**)words);
		ft_free_ntab(words);
		return (argv_len);
	}
}

/*
**	Returns a freshly allocated array of strings corresponding to the argv
**	parameter that should be passed on to the execve function.
**	Should be called after have used parse_expands and parse_redirections
**	on the token_head.
*/

char				**get_argv_from_token_lst(t_token *token_head)
{
	unsigned int	argv_len;
	t_token			*probe;

	if (!(probe = token_head))
		return (NULL);
	argv_len = 0;
	while (probe)
	{
		if (is_argv_token(probe))
			argv_len += token_length(probe);
		while (is_argv_token(probe))
			probe = probe->next;
		while (probe && probe->type == tk_eat)
			probe = probe->next;
		if (!probe || probe->type > tk_redirection)
			break ;
	}
	if (argv_len < 1)
		return (NULL);
	return (create_argv(token_head, argv_len));
}
