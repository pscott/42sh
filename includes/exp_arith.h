#ifndef EXP_ARITH_H
# define EXP_ARITH_H

/*
**	All possible tokens
*/

typedef enum		e_arith_token
{
	tk_nb = 1,
	tk_varplus = 2,
	tk_plusvar = 3,
	tk_varmin = 4,
	tk_minvar = 5,
	tk_add = 6,
	tk_sub = 7,
	tk_mult = 8,
	tk_div = 9,
	tk_mod = 10,
	tk_lesseq = 11,
	tk_moreeq = 12,
	tk_less = 13,
	tk_more = 14,
	tk_eq = 15,
	tk_noteq = 16,
	tk_operand = 17,
	tk_operor = 18,
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
long long			lonely_number(t_op *lst, int *err, char ***vars);
long long			check_err_numbers(t_op *lst);

char				*get_value_index(int i, char **env);
int					ft_str_isempty(const char *s);
void				initialize_long_long(long long *n1, long long *n2);

#endif
