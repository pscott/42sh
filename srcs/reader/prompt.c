#include "libterm.h"
#include "input.h"

void	print_prompt(t_st_prompt *st_prompt)
{
	ft_putstr(st_prompt->prompt);
}
