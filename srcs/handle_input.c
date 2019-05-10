#include "tosh.h"
#include "history.h"
#include "lexer.h"
#include "ast.h"

/*
** handle_input
** 1. get token_list from input
** 2. store input to history
** 3. get ast from token_list
** 4. execute ast
** 5. free ast
*/

t_hist_lst	*get_keep(t_hist_lst *hist_lst)
{
	t_hist_lst *probe;

	if (!(probe = hist_lst))
		return (NULL);
	while (probe->keep)
		probe = probe->next;
	return (probe);
}

t_hist_lst		*insert_left(t_hist_lst *hist_lst, char *line, char keep)
{
	t_hist_lst	*probe;
	t_hist_lst	*insert;

	insert = create_hist_lst(line, keep);
	if (!(probe = hist_lst))
		return (insert);
	else
	{
		if (probe->prev)
		{
			probe->prev->next = insert;
			insert->prev = probe->prev;
		}
		insert->next = probe;
		probe->prev = insert;
	}
	return (insert);
} // should no be in handle_input !

void	adjust_history(t_st_cmd *st_cmd, char *line)
{
	t_hist_lst	*to_insert;

	if (st_cmd->hist_lst->prev)
		to_insert = st_cmd->hist_lst->prev;
	else
		to_insert = st_cmd->hist_lst;
	if (to_insert->keep)
		insert_right(to_insert, line, 0);
	else
	{
		ft_memdel((void*)&to_insert->txt);
		to_insert->cpy = ft_strdup(line);
	}
}

t_bool	handle_input(t_st_cmd *st_cmd, char **env)
{
	t_ast			*ast_root;
	t_token			*token_head;
	int				lexer_ret;
	int				ret;
	char			*input;

	token_head = NULL;
	input = concatenate_txt(st_cmd);
	// need to append all st_cmd's txt
	while ((lexer_ret = lexer(input, &token_head, env)) == LEX_CONT_READ)
	{
		free_token_list(token_head);
		//free st_prompt
		adjust_history(st_cmd, input);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
	 	if ((ret = input_loop(st_cmd)) < 1)
		{
			if (ret == 0)
				print_line();
			return (0); // free stuff ?
		}
		input = concatenate_txt(st_cmd);
	}
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	insert_left(st_cmd->hist_lst, input, 1);
	ft_memdel((void*)&input);
	if (lexer_ret == LEX_FAIL)
	{
		free_token_list(token_head);
		ft_printf("\x1B[31m""### Lexer FAILED""\x1B[0m");
		print_line();
		return (0);
	}
/*	else
		ft_printf("\x1B[32m""### lexer SUCCESS""\x1B[0m");*/
	if (!(ast_root = create_ast(token_head)))
	{
		ft_printf("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		print_line();
		return (0);
	}
	//DEBUG_PARSER && ft_printf("\x1B[32m""### Parser SUCCESS""\x1B[0m""\n");
	exec_ast(ast_root, env);
	free_ast(ast_root);
	return (1);
}
