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
	while ((lexer_ret = lexer(input, &token_head)) == LEX_CONT_READ)
	{
		free_token_list(token_head);
		//free st_prompt
		adjust_history(st_cmd, input);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
	 	if ((ret = input_loop(st_cmd, vars)) < 1)
		{
			if (ret == 0)
				print_line();
			return (0); // free stuff ?
		}
		input = concatenate_txt(st_cmd);
		if (is_full_of_whitespaces(input))
			return (1);
	}
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	insert_left(st_cmd->hist_lst, input, 1);
	ft_memdel((void*)&input);
	if (lexer_ret == LEX_FAIL)
	{
		free_token_list(token_head);
		print_line();
		return (0);
	}
	print_token_list(token_head);
	if (!(ast_root = create_ast(token_head)))
	{
		//DEBUG_PARSER && ft_printf("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		print_line();
		return (0);
	}
	//print_ast(ast_root);
	exec_ast(ast_root, vars);
	free_ast(ast_root);
	return (1);
}
