#include "lexer.h"
#include "ast.h"

/*
**	Does not change token_head->type to TK_WORD because we need to know the
**	orginal type for redirections.
*/

static t_bool	expand_squotes(t_token *token_head)
{
	char	*old_content;

	if (*token_head->content == '\'' || *token_head->content == '"')
	{
		old_content = token_head->content;
		if (!(token_head->content = ft_strndup((const char*)&(*(token_head->content + 1)), ft_strlen(token_head->content) - 2)))
			ERROR_MEM;
		//do stuff: rien a faire ?
		free(old_content);
		return (1);
	}
	return (0);
}
static t_bool	is_valid_dquotes_escape(char c)
{
	if (c == '$' || c == '`' || c == '"' || c == '\\' || c == '\n')
		return (1);
	return (0);
}

static size_t	get_new_len(char *str, size_t old_len)
{
	size_t	i;
	size_t	res;

	i = 1;
	res = 0;
	//while (str[i] < old_len - 1)
	while (i < old_len - 1)
	{
		if (str[i] == '\\' && is_valid_dquotes_escape(str[i + 1]))
			i++;
		i++;
		res++;
	}
	return (res);//tmp
}

static t_bool	expand_dquotes(t_token	*token_head)
{
	char	*new_str;
	size_t	old_len;
	size_t	new_len;
	size_t	i;

	old_len = ft_strlen(token_head->content);
//	printf("new_len will be: %zu\n", get_new_len(token_head->content, old_len));
	new_len = get_new_len(token_head->content, old_len);
	if (!(new_str = ft_strnew(get_new_len(token_head->content, old_len))))
		ERROR_MEM;
	i = 1;
	while (i < new_len + 1)
	{
		if (token_head->content[i] == '\\' && is_valid_dquotes_escape(token_head->content[i + 1]))
		{
			ft_putendl("ESCAPE");
			token_head->content++;//degueu, can't free
		}
		new_str[i - 1] = token_head->content[i];
		//printf("NEW_STR: {%s}\n", new_str);
		i++;
	}
	//ft_memdel((void*)&token_head->content);//can't cause i moved the pointer
	token_head->content = new_str;
	return (1);//tmp
}

//it can contain " and ' ! but only trim the first and last: [0], [strlen(content)]
t_bool	parse_quotes(t_token *token_head)
{
	t_bool	res;

	res = 0;
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_SQ_STR)
		{
			res = 1;
			expand_squotes(token_head);
		}
		else if (token_head->type == TK_DQ_STR)
		{
			res = 1;
			expand_dquotes(token_head);
		}
		token_head = token_head->next;
	}
	return (res);
}
