/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:17 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:21 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "line_editing.h"
#include "lexer.h"
#include "ast.h"
#include "heredoc.h"

void		free_token_list(t_token *token_head)
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		probe = probe->next;
		ft_memdel((void*)&token_head->content);
		ft_memdel((void*)&token_head);
		token_head = probe;
	}
}

static void	free_ast_node(t_ast *node)
{
	free_token_list(node->token);
	ft_memdel((void*)&node);
}

void		free_ast(t_ast *ast_root)
{
	if (!ast_root)
		return ;
	if (ast_root->left)
		free_ast(ast_root->left);
	if (ast_root->right)
		free_ast(ast_root->right);
	free_ast_node(ast_root);
}

char		*free_get_doc(char *txt, char *eof, t_st_cmd *cmd,
	t_st_cmd *start_heredoc)
{
	clean_heredoc(cmd, start_heredoc);
	ft_strdel(&txt);
	ft_strdel(&eof);
	return (NULL);
}
