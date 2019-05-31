#ifndef EXPAND_H
# define EXPAND_H

# include "42sh.h"
# include "lexer.h"

char		*get_var_name(char *str);
void		substitute_env_var(t_token *token, size_t *i, const char *var_name
			, t_vars *vars);
char		*get_var_name(char *str);
t_bool		is_matched(const char *str
			, const char *begin_match, const char *end_match);
//t_bool		replace_all_arith_exp(char **str, size_t *index, t_vars *vars);
char		get_lowest_arith_exp(char **str, t_vars *vars);
t_bool		substitute_slice(char **old_str, size_t index[2], const char *to_sub);
void		substitute_param(t_token *token, size_t *i, const char *var_name
			, t_vars *vars);
t_bool		parse_param_sub(t_token *token, t_vars *vars);
t_bool		is_terminated(const char *open, const char *closed
			, const char *str);
const char	*get_param_sub_name(const char *str);
#endif
