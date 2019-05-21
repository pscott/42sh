#ifndef EXPAND_H
# define EXPAND_H

# include "42sh.h"
# include "lexer.h"

char		*get_var_name(char *str);
char		*substitute_env_var(char *old_str, size_t *i
		, char *var_value, char *var_name);

#endif
