#include "errors.h"
#include "ftsh.h"
#include "builtins.h"

int					case_fc(char **argv)
{
	t_st_fc			st_fc;
	t_st_cmd		*st_cmd;
	int				ret;

	ft_bzero(&st_fc, sizeof(st_fc));
	st_cmd = get_st_cmd(NULL);
	init_st_fc(st_cmd, &st_fc, argv);
	ret = 0;
	/*
	if (st_fc.flags[0] == 's')
		ret = case_fc_exec(st_cmd, &st_fc);
	else if (ft_strchr(st_fc.flags, 'l'))
		ret = case_fc_display(st_cmd, &st_fc);
	else
		ret = case_fc_editor(st_cmd, &st_fc);
		*/
	return (ret);
}
