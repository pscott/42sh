#include "libft.h"
#include "line_editing.h"

int				is_same_char(char a, char b)
{
	if (a == b)
		return (1);
	if (a <= 'Z' && a >= 'A' && a + 32 == b)
		return (1);
	if (a <= 'z' && a >= 'a' && a - 32 == b)
		return (1);
	return (0);
}
