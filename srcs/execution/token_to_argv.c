#include "ftsh.h"
#include "lexer.h"
#include "cmd_parsing.h"

/*
**	Utility function for fill_argv
**	Separates words in the string, filling the argv with the different words
*/

static void			apply_ifs(const char *string, char **argv, int *i)
{
	char			**words;
	int				j;

	if (!(words = ft_strsplit(string, IFS)))
		clean_exit(1, 1);
	j = 0;
	while (words[j])
	{
		argv[*i] = ft_strjoin_free_left(argv[*i], words[j]);
		j++;
		(*i)++;
	}
	if (j)
		(*i)--;
	ft_free_ntab(words);
}

/*
**	Fills the argv (applying IFS if needs be) until it encounters a token
**	that should not be in argv (tk_eat or type >= tk_pipe)
*/

static t_token		*fill_argv(t_token *token, char **argv, int *i)
{
	int				incremented;

	incremented = 0;
	while (is_argv_token(token))
	{
		if (token->type == tk_word)
			apply_ifs(token->content, argv, i);
		else
		{
			if (!(argv[*i] = ft_strjoin_free_left(argv[*i], token->content)))
				clean_exit(1, 1);
		}
		if (ft_strlen(argv[*i]) == 0)
		{
			ft_strdel(&argv[*i]);
			argv[*i] = ft_strdup("");
		}
		incremented = 1;
		token = token->next;
	}
	*i += incremented;
	return (token);
}

/*
**	Utility function for get_argv_from_token_lst.
**	Returns the freshly allocated argv.
*/

static char			**create_argv(t_token *token_head, int argv_len)
{
	char			**argv;
	int				i;

	if (!(argv = (char**)malloc(sizeof(*argv) * (argv_len + 1))))
		clean_exit(1, 1);
	ft_bzero(argv, sizeof(*argv) * (argv_len + 1));
	i = 0;
	while (i < argv_len)
	{
		token_head = fill_argv(token_head, argv, &i);
		while (token_head && token_head->type == tk_eat)
			token_head = token_head->next;
	}
	return (argv);
}

/*
**	Utility function for get_argv_from_token_lst
**	Returns the number of separated words until the next token_eat or pipe,
**	and changes the address of probe_token accordingly.
*/

static int			token_length(t_token **probe)
{
	int				argv_len;
	int				words_len;
	char			**words;

	argv_len = 0;
	while (is_argv_token(*probe))
	{
		if ((*probe)->type == tk_word)
		{
			words = ft_strsplit((*probe)->content, IFS);
			words_len = ft_ntab_len((const char**)words);
			words_len = words_len ? words_len : 1;
			ft_free_ntab(words);
		}
		else
			words_len = 1;
		argv_len += argv_len ? words_len - 1 : words_len;
		*probe = (*probe)->next;
	}
	return (argv_len);
}

/*
**	outdated
**	Returns a freshly allocated array of strings corresponding to the argv
**	parameter that should be passed on to the execve function.
**	Should be called after have used parse_expands and parse_redirections
**	on the token_head.
*/

int					get_argv_from_token_lst(t_token *token_head, char ***argv)
{
	int				argv_len;
	t_token			*probe;

	if (!(probe = token_head))
		return (1);
	argv_len = 0;
	while (probe)
	{
		if (probe->type == tk_word && !ft_strlen(probe->content)
				&& probe->next && probe->next->type == tk_eat)
		{
			probe->type = tk_eat;
			probe = probe->next;
		}
		else if (is_argv_token(probe))
			argv_len += token_length(&probe);
		while (probe && probe->type == tk_eat)
			probe = probe->next;
		if (!probe || probe->type > tk_redirection)
			break ;
	}
	if (argv_len < 1)
		return (1);
	*argv = create_argv(token_head, argv_len);
	return (0);
}
