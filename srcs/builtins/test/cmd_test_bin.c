#include "builtins.h"

int				test_flag_eq(char *left, char *right, int *result)
{
	long long	vleft;
	long long	vright;

	if (check_longlong(left, &vleft))
		return (2);
	if (check_longlong(right, &vright))
		return (2);
	if (vleft == vright)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int				test_flag_ne(char *left, char *right, int *result)
{
	long long	vleft;
	long long	vright;

	if (check_longlong(left, &vleft))
		return (2);
	if (check_longlong(right, &vright))
		return (2);
	if (vleft != vright)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int				test_flag_ge(char *left, char *right, int *result)
{
	long long	vleft;
	long long	vright;

	if (check_longlong(left, &vleft))
		return (2);
	if (check_longlong(right, &vright))
		return (2);
	if (vleft >= vright)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int				test_flag_lt(char *left, char *right, int *result)
{
	long long	vleft;
	long long	vright;

	if (check_longlong(left, &vleft))
		return (2);
	if (check_longlong(right, &vright))
		return (2);
	if (vleft < vright)
		*result = 0;
	else
		*result = 1;
	return (0);
}

int				test_flag_le(char *left, char *right, int *result)
{
	long long	vleft;
	long long	vright;

	if (check_longlong(left, &vleft))
		return (2);
	if (check_longlong(right, &vright))
		return (2);
	if (vleft <= vright)
		*result = 0;
	else
		*result = 1;
	return (0);
}
