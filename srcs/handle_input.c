#include "ftsh.h"
#include "lexer.h"
#include "ast.h"
#include "libterm.h"
#include "history.h"

/*
** handle_input
** 1. get token_list from input
** 2. store input to history
** 3. get ast from token_list
** 4. execute ast
** 5. free ast
*/

t_bool	handle_input(t_st_cmd *st_cmd, t_vars *vars)
{
	t_ast			*ast_root;
	t_token			*token_head;
	int				lexer_ret;
	int				ret;
	char			*input;

	token_head = NULL;
	input = concatenate_txt(st_cmd);
	while ((lexer_ret = lexer(input, &token_head, vars)) == lex_cont_read)
	{
		free_token_list(token_head);
		adjust_history(st_cmd, input, 0);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
	 	if (((ret = input_loop(st_cmd, vars, regular)) < 1) || !*st_cmd->st_txt->txt)
		{
			ft_strdel(&input); // need \n ?
			return (0);
		}
		ft_strdel(&input);
		input = concatenate_txt(st_cmd);
		if (is_full_of_whitespaces(input))
		{
			ft_strdel(&input);
			return (1);
		}
	}
	adjust_history(st_cmd, input, 1);
	ft_strdel(&input);
	if (lexer_ret == lex_fail)
	{
		free_token_list(token_head);
		return (0);
	}
	if (!(ast_root = create_ast(token_head)))
		return (0);
	vars->cmd_value = exec_ast(ast_root, vars); // might be causing errors with exit statuses...
	free_ast(ast_root);
	return (1);
}
