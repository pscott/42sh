#include "42sh.h"
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
		if (isatty(STDIN_FILENO) == 0)
			return (0);
		adjust_history(st_cmd, input);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
		get_st_cmd(&st_cmd);
	 	if ((ret = input_loop(st_cmd, vars)) < 1)
		{
			if (ret == 0)
				ft_strdel(&input); // need \n ?
			return (0);
		}
		if (!*st_cmd->st_txt->txt)
		{
			ft_strdel(&input);
			return (0);
		}
		input = concatenate_txt(st_cmd);
		if (is_full_of_whitespaces(input))
		{
			ft_strdel(&input);
			return (1);
		}
	}
	print_token_list(token_head);//debug
	adjust_history(st_cmd, input);
	if (st_cmd->hist_lst && st_cmd->hist_lst->keep == 0)
		st_cmd->hist_lst->keep = 1;
	else
		insert_left(st_cmd->hist_lst, input, 1);
	ft_strdel(&input);
	if (lexer_ret == lex_fail)
	{
		free_token_list(token_head);
		return (0);
	}
	if (!(ast_root = create_ast(token_head)))
		return (0);
	exec_ast(ast_root, vars);
	free_ast(ast_root);
	return (1);
}
