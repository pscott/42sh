#include "line_editing.h"
#include "history.h"

/*
**	Frees the st_cmd, WITHOUT freeing history.
*/

void			free_st_cmd(t_st_cmd *st_cmd)
{
	if (!st_cmd)
		return ;
	free_st_txt(&st_cmd->st_txt);
	free_st_prompt(&st_cmd->st_prompt);
	ft_memdel((void*)&st_cmd);
}

/*
**	Goes back to the beginning of the st_cmd list and frees every node in there.
**	Frees history.
*/

void			free_all_st_cmds(t_st_cmd **st_cmd)
{
	t_st_cmd	*probe;
	t_st_cmd	*tmp;

	if (!st_cmd || !(*st_cmd))
		return ;
	probe = get_first_st_cmd(*st_cmd);
	free_hist_lst(probe->hist_lst);
	if ((*st_cmd)->hist_len)
		free((*st_cmd)->hist_len);
	free((*st_cmd)->window);
	while (probe)
	{
		tmp = probe;
		probe = probe->next;
		free_st_cmd(tmp);
	}
}
