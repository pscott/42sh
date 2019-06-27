#include "ftsh.h"
#include "input.h"
#include "heredoc.h"

int		get_doc_ctrl_d(int *ctrl_d, char *eof, char **txt, t_st_cmd *cmds[2])
{
	*ctrl_d = 1;
	ft_dprintf(STDERR_FILENO, SHELL_NAME "%s `%s')\n", CTRL_D_ERR, eof);
	*txt = concatenate_heredoc_txt(cmds[0], cmds[1]);
	return (1);
}

int		is_e(int len, char *txt, char *eof)
{
	if (len > 0 && !ft_strncmp(&txt[len], eof, ft_strlen(eof))
		&& txt[len - 1] == '\n' && txt[ft_strlen(txt) - 1] == '\n')
		return (1);
	return (0);
}
