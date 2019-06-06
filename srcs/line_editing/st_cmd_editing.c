#include "line_editing.h"
#include "history.h"

t_st_cmd		*append_st_cmd(t_st_cmd *st_cmd, const char *txt,
				const char *prompt)
{
	t_st_cmd	*new;

	if (!(new = (t_st_cmd*)malloc(sizeof(*new))))
		clean_exit(1, 1);
	new->st_txt = init_st_txt((const char*)txt);
	new->st_prompt = init_st_prompt(prompt);
	new->window = st_cmd->window;
	retrieve_pos(&new->start_pos);
	init_relative_pos(new);
	new->hist_lst = st_cmd->hist_lst;
	st_cmd->next = new;
	new->prev = st_cmd;
	new->next = NULL;
	return (new);
}

t_st_cmd		*reset_st_cmd(t_st_cmd *old_st_cmd)
{
	t_st_cmd	*st_cmd;
	t_st_cmd	*left_cmd;

	if (!(st_cmd = (t_st_cmd*)malloc(sizeof(*st_cmd))))
		clean_exit(1, 1);
	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->st_prompt = init_st_prompt(NULL);
	retrieve_pos(&st_cmd->start_pos);
	st_cmd->window = old_st_cmd->window;
	init_relative_pos(st_cmd);
	st_cmd->hist_lst = old_st_cmd->hist_lst;
	old_st_cmd = get_first_st_cmd(old_st_cmd);
	while (old_st_cmd)
	{
		left_cmd = old_st_cmd;
		old_st_cmd = old_st_cmd->next;
		free_st_cmd(left_cmd);
	}
	st_cmd->next = NULL;
	st_cmd->prev = NULL;
	get_st_cmd(&st_cmd);
	return (st_cmd);
}

/*
**	Function to initialize st_cmd
*/

t_st_cmd		*init_st_cmd(const char **env)
{
	t_st_cmd	*st_cmd;

	if (!(st_cmd = (t_st_cmd*)malloc(sizeof(*st_cmd))))
		clean_exit(1, 1);
	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->st_prompt = init_st_prompt(NULL);
	st_cmd->window = init_window_struct();
	if (isatty(STDIN_FILENO))
	{
		init_relative_pos(st_cmd);
		st_cmd->hist_lst = get_history(env);
		st_cmd->hist_lst = insert_right(st_cmd->hist_lst, "last", 0);
	}
	st_cmd->next = NULL;
	st_cmd->prev = NULL;
	return (st_cmd);
}

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
	free((*st_cmd)->window);
	while (probe)
	{
		tmp = probe;
		probe = probe->next;
		free_st_cmd(tmp);
	}
}
