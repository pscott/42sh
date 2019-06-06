#include "line_editing.h"

int	check_for_words(t_st_cmd *st_cmd, const char *buf)
{
	if (ft_strncmp(buf, "\x02", 2) == 0)
	{
		jump_words(st_cmd, -1);
		return (1);
	}
	else if (ft_strncmp(buf, "\x06", 2) == 0)
	{
		jump_words(st_cmd, 1);
		return (1);
	}
	else
		return (0);
}
