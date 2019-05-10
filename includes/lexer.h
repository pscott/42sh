#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>//tejme

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "libft.h"
# include "libterm.h"

# define ERROR_MEM clean_exit(1);
# define OP_CHART_SIZE 22

typedef unsigned char	t_bool;

/*
** TK_EAT should always be 0
** then in increasing order:
** Words (simple word, Squot, Dquot, Monochar ?)
** Redirections
** Pipe
** AND OR
** AMP
** SEMI
*/

typedef enum		e_token_type
{
	TK_EAT,
	TK_WORD,//1
	TK_MONOC,
	TK_SQ_STR,
	TK_DQ_STR,
	TK_REDIRECTION,
	TK_HEREDOC,
	TK_PIPE,
	TK_AND,//=OR
	TK_OR,//=AND
	TK_AMP,
	TK_SEMI,
	TK_42SH
}					t_token_type;

typedef struct		s_token
{
	char			*content;
	size_t			size;
	t_token_type	type;
	struct s_token	*next;
}					t_token;


typedef struct		s_operation
{
	char			str[4];
	unsigned char	size;
	t_token_type	type;
}					t_operation;

typedef enum		s_lexer_state
{
	LEX_FAIL,
	LEX_SUCCESS,
	LEX_CONT_READ
}					t_lexer_state;

//DEBUG TEJME
void	print_token(t_token *token);
void	print_token_list(t_token *token_head);
//

/*
** get_token.c
*/

t_token	*get_token(char **cmdline, t_operation *op_chart);
t_token	*create_token(char *cmdline, size_t size, t_token_type type);

/*
** lexer_op_chart.c
*/

t_token		*get_op_chart_token(char **cmdline, t_operation *op_chart);
t_operation	*get_op_chart(void);
void		print_op_table(t_operation *op_chart);//debug

#endif
