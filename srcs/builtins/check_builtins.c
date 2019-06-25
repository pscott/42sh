#include "builtins.h"

static int	check_remaining_builtins(const char *cmd)
{
	if (ft_strequ(cmd, "fc"))
		return (cmd_fc);
	else if (ft_strequ(cmd, "history"))
		return (cmd_history);
	else if (ft_strequ(cmd, "test"))
		return (cmd_test);
	else if (ft_strequ(cmd, "set"))
		return (cmd_set);
	else if (ft_strequ(cmd, "unset"))
		return (cmd_unset);
	else if (ft_strequ(cmd, "export"))
		return (cmd_export);
	else if (ft_strequ(cmd, "jobs"))
		return (cmd_jobs);
	else if (ft_strequ(cmd, "fg"))
		return (cmd_fg);
	else if (ft_strequ(cmd, "bg"))
		return (cmd_bg);
	return (cmd_error);
}

/*
**	Checks if arg[0] is a builtin or not. Returns the corresponding enum
**	command value in case of success ; returns 0 on failure.
*/

int			check_builtins(const char *cmd)
{
	if (ft_strequ(cmd, "exit"))
		return (cmd_exit);
	else if (ft_strequ(cmd, "cd"))
		return (cmd_cd);
	else if (ft_strequ(cmd, "type"))
		return (cmd_type);
	else if (ft_strequ(cmd, "hash"))
		return (cmd_hash);
	else if (ft_strequ(cmd, "echo"))
		return (cmd_echo);
	else
		return (check_remaining_builtins(cmd));
}
