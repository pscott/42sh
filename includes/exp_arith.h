/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_arith.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:07 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:11 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_ARITH_H
# define EXP_ARITH_H

/*
**	All possible tokens
*/

typedef enum		e_arith_token
{
	TK_NB = 1,
	TK_VARPLUS = 2,
	TK_PLUSVAR = 3,
	TK_VARMIN = 4,
	TK_MINVAR = 5,
	TK_ADD = 6,
	TK_SUB = 7,
	TK_MULT = 8,
	TK_DIV = 9,
	TK_MOD = 10,
	TK_LESSEQ = 11,
	TK_MOREEQ = 12,
	TK_LESS = 13,
	TK_MORE = 14,
	TK_EQ = 15,
	TK_NOTEQ = 16,
	TK_OPERAND = 17,
	TK_OPEROR = 18,
}					t_arith_token;

/*
**	Structure for ast
*/

typedef struct		s_op
{
	int				token;
	long long		value;
	int				varid;
	char			*varname;
	int				beg;
	int				end;
	char			parent;
	struct s_op		*left;
	struct s_op		*right;
	struct s_op		*prev;
}					t_op;

/*
**	Structure for lexer
*/

typedef struct		s_tok
{
	int				token;
	long long		value;
	int				varid;
	char			*varname;
	int				beg;
	int				end;
}					t_tok;

/*
**	Structure for tokenizer vars
*/

typedef struct		s_integ
{
	size_t			i;
	int				k;
	int				prev;
	int				moins;
}					t_integ;

int					is_oper(char *str);
t_op				*create_op_link(int token, long long value, t_tok link);
t_op				*build_op_list(t_tok *tokens);
int					op_tokenizer(char *str, t_tok **tokens, char ***vars);
int					get_op_token(char *str, int varid, int prev_prev_tk);
void				put_lst_right(t_op *lst, t_op *new);
void				put_lst_left(t_op *lst, t_op *new);
int					free_lst(t_op *lst, int err);
void				put_lst_right(t_op *lst, t_op *new);
void				put_lst_left(t_op *lst, t_op *new);
void				put_lst_back(t_op *lst, t_op *new);
int					check_chars(char *str, t_vars *vars);
long long			ft_atoll(char *str);
char				*ft_lltoa(long long n);
int					expansion_arith(char *str, long long *result
					, t_vars *vars);
int					free_tokens(t_tok *tokens, int ret);

int					get_nb_len(char *str);
void				clean_done_token(char *str, int len);
int					get_tok_len(t_tok *tok);
int					is_var(char *str);
int					check_next_tok(t_tok *dirty, int i);
int					init_toks_dirty(t_tok **tokens, char *str);
void				d_number(t_tok **tokens, size_t *i, int *k, char **str);
int					d_variable(t_tok **t, t_integ *it, char **s, char ***v);
void				d_operator(t_tok **tokens, size_t *i, int *k, char **str);
int					init_toks_clean(t_tok *dirty, t_tok **clean);
void				c_iter(t_tok *d, t_tok **c, int *i, int *k);
int					check_put_oper(int prev, t_tok *dirty, int i);
void				invert_value(int *i);
void				insert_clean_token(t_tok *d, t_tok **c, t_integ *v);
int					c_number(t_tok *d, t_tok **c, t_integ *v);
void				c_operator(t_tok *d, t_tok **c, t_integ *v);

int					exec_op_list(t_op *lst, char ***vars, long long *result);
int					get_var_value(t_op *lst, long long *nb, char ***vars);
long long			calcul(long long nb1, long long nb2, int token, int *error);
long long			oper_and_or(t_op *lst, int *err, char ***vars);
long long			return_set_err(int *err, int error);
long long			double_numbers(t_op *lst, int *err, char ***vars);
long long			not_tok_nb(t_op *lst, int *err, long long *nb, char ***var);
long long			exec(t_op *lst, int *err, char ***vars);
long long			lonely_number(t_op *lst, char ***vars);
long long			check_err_numbers(t_op *lst);

char				*get_value_index(int i, char **env);
int					ft_str_isempty(const char *s);
void				initialize_long_long(long long *n1, long long *n2);

#endif
