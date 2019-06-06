#include "line_editing.h"

int	check_for_words(t_st_cmd *st_cmd, const char *buf)
{
	if (ft_strncmp(buf, ALT_LEFT, ALT_LEFT_LEN + 1) == 0)
	{
		jump_words(st_cmd, -1);
		return (1);
	}
	else if (ft_strncmp(buf, ALT_RIGHT, ALT_RIGHT_LEN + 1) == 0)
	{
		jump_words(st_cmd, 1);
		return (1);
	}
	else
		return (0);
}
