#ifndef HEREDOC_H
# define HEREDOC_H

# include "42sh.h"
# include "lexer.h"
# include "input.h"

# define HEREDOC_FILENAME "/tmp/.tmp_heredoc"
# define MAX_INT_LEN 10
# define UINT_MAX 4294967295

char	*eof_join(char *eof, t_token *token);
char	*find_uniq_filename(void);
t_bool	parse_heredoc(t_token *token_head, t_vars *vars);
#endif
