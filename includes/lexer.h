#ifndef LEXER_H
# define LEXER_H

# include "42sh.h"
# include <stdlib.h>
# include "libft.h"

# define OP_CHART_SIZE 21
# define DEBUG_PARSER 0

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
	tk_eat,
	tk_word,//1
	tk_monoc,
	tk_sq_str,
	tk_dq_str,
	tk_redirection,
	tk_heredoc,
	//tk_arith_exp,//useless
	//tk_param_sub,//useless
	tk_pipe,
	tk_and,//=or
	tk_or,//=and
	tk_amp,
	tk_semi,
	tk_42sh,
	tk_unsupported
}					t_token_type;

typedef struct		s_token
{
	char			*content;
	size_t			size;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

//t_bool	save_heredoc(t_token **prev_token, t_token **current_token, struct s_vars *vars);

typedef struct		s_operation
{
	char			str[4];
	unsigned char	size;
	t_token_type	type;
}					t_operation;

typedef enum		s_lexer_state
{
	lex_fail,
	lex_success,
	lex_cont_read
}					t_lexer_state;

//DEBUG TEJME
void	print_token(t_token *token);
void	print_token_list(t_token *token_head);
//

/*
** lexer.c
*/

t_token				*create_token(char *cmdline, size_t size
					, t_token_type type);
//int					lexer(char *cmdline, t_token **token_head, struct s_vars *vars);
int					lexer(char *cmdline, t_token **token_head, t_vars *vars);

/*
** lexer utils
*/

t_bool				is_argv_token(t_token *probe);
t_bool				is_simple_cmd_token(t_token *probe);
t_bool				is_logic_or_pipe(t_token *token);
t_bool				is_two_ctrlop_or_redir_following(t_token *prev_token
					, t_token *current_token);
t_bool				token_list_start_with_ctrl_op(t_token *prev_token
					, t_token *current_token);
t_bool				is_redir_token(t_token *token);
t_bool				is_ctrl_op_token(t_token *token);
t_token				*copy_tokens(t_token *token_head);

/*
** Get_token.c
*/

t_token	*get_token(char **cmdline, t_operation *op_chart);
//t_token	*check_arith_exp_token(char **cmdline);
t_token	*create_token(char *cmdline, size_t size, t_token_type type);

/*
** Lexer_op_chart.c
*/

t_token		*get_op_chart_token(char **cmdline, t_operation *op_chart);
t_operation	*get_op_chart(void);
void		print_op_table(t_operation *op_chart);//debug

/*
** Free functions
*/

void				free_token_list(t_token *token_head);


//test
char	*get_lowest_arith_exp(char *str, t_vars *vars);
#endif
