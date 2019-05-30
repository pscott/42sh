#ifndef EXPAND_H
# define EXPAND_H

# include "42sh.h"
# include "lexer.h"

char		*get_var_name(char *str);
char		*substitute_env_var(char *old_str, size_t *i
			, const char *var_value, const char *var_name);
char		*get_var_name(char *str);
t_bool		is_matched(const char *str
			, const char *begin_match, const char *end_match);
t_bool		replace_all_arith_exp(char **str, size_t *index, t_vars *vars);
#endif
