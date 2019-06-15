#include "ftsh.h"
#define PATH_DEFAULT_VALUE "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

void	set_default_shell_vars(t_vars *vars)
{
	char	*str;

	if (get_varline_from_vartab("PATH", vars->shell_vars) == NULL)
	{
		//use add_variables here
		//str = concat_for_vartab("PATH", PATH_DEFAULT_VALUE);

	}
}
