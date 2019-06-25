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
	init_relative_pos(&new->cursor_pos, new->window, new->st_prompt->size);
	new->hist_lst = st_cmd->hist_lst;
	new->keep = st_cmd->keep;
	new->cr = st_cmd->cr;
	st_cmd->next = new;
	new->prev = st_cmd;
	new->next = NULL;
	return (new);
}

static void		init_values(int *keep, int *cr)
{
	*keep = 1;
	*cr = 0;
}

t_st_cmd		*reset_st_cmd(t_st_cmd *old_st_cmd)
{
	t_st_cmd	*st_cmd;
	t_st_cmd	*left_cmd;

	if (!(st_cmd = (t_st_cmd*)malloc(sizeof(*st_cmd))))
		clean_exit(1, 1);
	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->st_prompt = init_st_prompt(NULL);
	st_cmd->window = old_st_cmd->window;
	st_cmd->is_cr_sqt = 0;
	init_values(&st_cmd->keep, &st_cmd->cr);
	init_relative_pos(&st_cmd->cursor_pos, st_cmd->window,
		st_cmd->st_prompt->size);
	st_cmd->hist_lst = old_st_cmd->hist_lst;
	st_cmd->hist_len = old_st_cmd->hist_len;
	*st_cmd->hist_len = get_hist_len(st_cmd->hist_lst);
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
	int			*hist_len_var;

	if (!(st_cmd = (t_st_cmd*)malloc(sizeof(*st_cmd))))
		clean_exit(1, 1);
	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->st_prompt = init_st_prompt(NULL);
	st_cmd->is_cr_sqt = 0;
	st_cmd->window = init_window_struct();
	st_cmd->keep = 1;
	init_relative_pos(&st_cmd->cursor_pos, st_cmd->window,
		st_cmd->st_prompt->size);
	if (!(hist_len_var = (int*)malloc(sizeof(int))))
		clean_exit(1, 1);
	st_cmd->cr = 0;
	st_cmd->hist_len = hist_len_var;
	st_cmd->hist_lst = get_history(env);
	st_cmd->hist_lst = insert_right(st_cmd->hist_lst, "", 0);
	*hist_len_var = get_hist_len(st_cmd->hist_lst);
	st_cmd->next = NULL;
	st_cmd->prev = NULL;
	return (st_cmd);
}
