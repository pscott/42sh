#include "builtins.h"

int		test_flag_sym_eq(char *left, char *right, int *result)
{
	if (ft_strequ(left, right))
		*result = 0;
	else
		*result = 1;
	return (0);
}

int		test_flag_sym_noteq(char *left, char *right, int *result)
{
	if (!ft_strequ(left, right))
		*result = 0;
	else
		*result = 1;
	return (0);
}
