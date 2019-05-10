#include "tosh.h"
#include "lexer.h"

/*
** create_token
** malloc the token,
** strndup(cmdline, size) into ->content,
** set ->size and ->type
** then return the token
*/

t_token	*create_token(char *cmdline, size_t size, t_token_type type)
{
	t_token	*new_token;

	if (!(new_token = (t_token*)malloc(sizeof(t_token))))
	{
		ft_putendl_fd("malloc failed in create_token", STDERR_FILENO);
		//ERROR_MEM;
		return (NULL);
	}
	new_token->size = size;
	new_token->type = type;
	new_token->next = NULL;
	if (!(new_token->content = ft_strndup(cmdline, size)))
	{
		ft_memdel((void*)&new_token);
		ft_putendl_fd("malloc failed in create_token", STDERR_FILENO);
		//ERROR_MEM;
		return (NULL);
	}
	return (new_token);
}

/*
** add_token_to_list
** 1. check syntax (if start with '&&', or 2 '&&' are following)
** 2. check here_doc ???
** 3. create a token_list or append it with the given token
*/

static t_bool	add_token_to_list(t_token *current_token, t_token *prev_token
				, t_token **token_head)
{
	t_token	*probe;

	if (token_list_start_with_ctrl_op(prev_token, current_token)
			|| is_two_ctrlop_or_redir_following(prev_token, current_token))
		return (0);
	if (prev_token && prev_token->type == TK_HEREDOC
			&& current_token->type != TK_EAT)
	{
		printf("HEREDOC, enter READ_MODE, with EOF: {%s}\n", current_token->content);
		//system("read -p \"press ENTER to continue\"");
	}
	if (!(*token_head))
	{
		*token_head = current_token;
		return (1);
	}
	probe = *token_head;
	while (probe->next)
		probe = probe->next;
	probe->next = current_token;
	return (1);
}

/*
** init_lexer
** set the variables the lexer needs
*/

static void	init_lexer(t_operation **op_chart, t_token **token_head
			, t_token **prev_token)
{
	*op_chart = get_op_chart();
	*token_head = NULL;
	*prev_token = NULL;
}

/*
** lexer
** - run through the cmdline and tokenize it
** - return LEX_CONT_READ when the cmdline is not complete, so handle_input()
** continue reading and append the new input to cmdline
** - return LEX_FAIL and output the message accordignly if the cmdline isn't
** valid
** - return LEX_SUCCES otherwise, so handle_input can continue
*/

int		lexer(char *cmdline, t_token **token_head, char **env)
{
	t_token		*current_token;
	t_operation	*op_chart;
	t_token		*prev_token;

	(void)env;//no need for env in lexer ?
	init_lexer(&op_chart, token_head, &prev_token);
	while (cmdline && *cmdline)
	{
		if (!(current_token = get_token(&cmdline, op_chart)))
			return (LEX_CONT_READ);
		if (!(add_token_to_list(current_token, prev_token, token_head)))
			return (LEX_FAIL);
		if (current_token->type != TK_EAT)
			prev_token = current_token;
	}
	if (is_logic_or_pipe(current_token)
			|| (is_logic_or_pipe(prev_token) && !current_token->type))
	{
		ft_printf("tmp, tklst end with '&&', '||' or '|': READ_MODE");
		print_line();
		return (LEX_CONT_READ);
	}
	else if (prev_token && is_redir_token(prev_token)
			&& (!current_token->type || is_redir_token(current_token)))
	{
		ft_putstr("222 ");
		syntax_error_near(current_token);
		return (LEX_FAIL);
	}
	return (LEX_SUCCESS);
}
