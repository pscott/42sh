#ifndef LEXER_H
# define LEXER_H

# include "ftsh.h"

# define OP_CHART_SIZE 19
# define DEBUG_PARSER 0

/*
** TK_EAT should always be 0
** then in increasing order:
** Words (simple word, Monochar, Squot, Dquot)
** Redirections
** Pipe
** AND OR
** AMP
** SEMI
*/

typedef enum			e_token_type
{
	tk_eat,
	tk_word,
	tk_monoc,
	tk_sq_str,
	tk_dq_str,
	tk_redirection,
	tk_heredoc,
	tk_pipe,
	tk_and,
	tk_or,
	tk_amp,
	tk_semi,
	tk_42sh,
	tk_unsupported
}						t_token_type;

typedef struct			s_operation
{
	char				str[4];
	unsigned char		size;
	t_token_type		type;
}						t_operation;

typedef struct			s_token
{
	char				*content;
	struct s_token		*next;
	size_t				size;
	t_token_type		type;
}						t_token;

typedef enum			e_lexer_state
{
	lex_success,
	lex_cont_read,
	lex_fail
}						t_lexer_state;

/*
**	For debugging: remove it afterwards
*/

void					print_token(t_token *token);
void					print_token_list(t_token *token_head);
void					print_op_table(t_operation *op_chart);

/*
** lexer.c
*/

t_token					*create_token(char *cmdline, size_t size,
	t_token_type type);
int						lexer(char *cmdline, t_token **token_head,
	t_vars *vars);

/*
** lexer utils
*/

int						is_argv_token(t_token *probe);
int						is_simple_cmd_token(t_token *probe);
int						is_logic_or_pipe(t_token *token);
int						is_two_ctrlop_or_redir_following(t_token *prev_token,
	t_token *current_token);
int						token_list_start_with_ctrl_op(t_token *prev_token,
	t_token *current_token);
int						is_redir_token(t_token *token);
int						is_ctrl_op_token(t_token *token);
t_token					*copy_tokens(t_token *token_head);

/*
** Get_token.c
*/

t_token					*get_token(char **cmdline, t_operation *op_chart);
t_token					*create_token(char *cmdline, size_t size,
	t_token_type type);

/*
** Lexer_op_chart.c
*/

t_token					*get_op_chart_token(char **cmdline,
	t_operation *op_chart);
t_operation				*get_op_chart(void);

/*
** Free functions
*/

void					free_token_list(t_token *token_head);

/*
** check_special_token.c
*/

t_token					*check_arith_exp_token(char **cmdline);
t_token					*check_param_sub_token(char **cmdline);

/*
** lexer_escape_tools.c
*/

int						adjust_escaped(char c, int escaped);
t_token					*trim_escaped_newline(void);
t_token					*get_eat_token(char **cmdline);
#endif
