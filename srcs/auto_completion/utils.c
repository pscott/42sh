#include "auto_completion.h"

unsigned int		get_cols_term(void)
{
	struct winsize	s;

	update_window_struct(&s);
	return (s.ws_col);
}

unsigned int		get_columns_display(unsigned int count, unsigned int maxlen)
{
	unsigned int	cols;

	cols = get_cols_term() / (maxlen + 1);
	if (!cols)
		cols = 1;
	if ((maxlen + 1) * count < get_cols_term())
		cols = count;
	return (cols);
}

unsigned int		get_rows_display(unsigned int count, unsigned int cols)
{
	if (count % cols == 0)
		return (count / cols);
	else
		return ((count / cols) + 1);
}

void				initialize_str(char **s1, char **s2, char **s3,
					char **s4)
{
	if (s1)
		*s1 = NULL;
	if (s2)
		*s2 = NULL;
	if (s3)
		*s3 = NULL;
	if (s4)
		*s4 = NULL;
}

void				get_pwd_and_pwd_slash(char **pwd, char **pwd_slash)
{
	if (!(*pwd = getcwd(*pwd, PATH_MAX)))
		return ;
	if (!(*pwd_slash = ft_strjoin(*pwd, "/")))
		clean_exit(1, 1);
}
