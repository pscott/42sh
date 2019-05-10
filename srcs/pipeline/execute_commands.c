#include "lexer.h"
#include "builtins.h"
#include "ast.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char			*res;
	unsigned int	s1_len;

	//dprintf(2, "Joining: {%s} with {%s}", s1, s2);
	//print_line();
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	if (!(res = ft_strnew(s1_len + ft_strlen(s2))))
		ERROR_MEM;
	ft_strcpy(res, s1);
	ft_strcat(&res[s1_len], s2);
	ft_strdel(&s1);
	//dprintf(2, "RESULT: {%s}\n", res);
	return (res);
}

static char	*concatenate_strings(t_token *token)
{
	char	*res;

	if (!token)
		return (NULL);
	res = NULL;
	while (is_argv_token(token))
	{
		res = ft_strjoin_free(res, token->content);
		token->type = TK_EAT;
		token = token->next;
	}
	return (res);
}

static char	**create_argv(t_token *token_head, unsigned int argv_len)
{
	char			**res;
	unsigned int	i;

	if (!(res = (char**)malloc(sizeof(*res) * (argv_len + 1))))
		return (NULL);//ERROR_MEM;
	i = 0;
	res[argv_len] = NULL;
	//ft_dprintf(2, "HEAD: %s, len: %u", token_head->content, argv_len);
	//print_line();
	while (i < argv_len)
	{
		if (is_argv_token(token_head))
		{
			res[i] = concatenate_strings(token_head); //protect ?
			i++;
		}
		while (is_argv_token(token_head))
			token_head = token_head->next;
		while (token_head && token_head->type == TK_EAT)
			token_head = token_head->next;
	}
	return (res);
}

t_bool		execute_argv(char	**argv)
{
	int	ret;

	if (!argv)
		return (0);
	if (reset_terminal_settings() == 0)
		clean_exit(1); // ?
//	reset_dfl();
	if ((ret = check_builtins(argv)))
		return (exec_builtins(argv, ret));
	else if (execve(argv[0], (char * const*)argv, (char* const*)g_env))
	{
		ft_dprintf(2, "----- Failed to execute ! -----\n");
		clean_exit(1);
	}
	return (1);
}

t_bool		execute_tokens(t_token *token_head)
{
	unsigned int	argv_len;
	t_token			*probe;

	if (!(probe = token_head))
		return (0);
	argv_len = 0;
	while (probe)
	{
		if (is_argv_token(probe))
			argv_len++;
		while (is_argv_token(probe))
			probe = probe->next;
		while (probe && probe->type == TK_EAT)
			probe = probe->next;
		if (!probe || probe->type > TK_REDIRECTION)
			break;
	}
	if (argv_len < 1)
	{
		ft_dprintf(2, "Something went wrong: nothing to execute..\n");
		return (0);
	}
	return (execute_argv(create_argv(token_head, argv_len)));
}
