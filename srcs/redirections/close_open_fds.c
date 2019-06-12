#include "cmd_parsing.h"

static	void	create_fd_save(int fd, t_c_lst **lst)
{
	t_c_lst		*new;
	t_c_lst		*ptr;

	if (!(new = (t_c_lst*)malloc(sizeof(t_c_lst))))
		clean_exit(1, 1);
	new->fd = fd;
	new->next = NULL;
	if (!(*lst))
		(*lst) = new;
	else
	{
		ptr = (*lst);
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

static	void	del_fd_save(t_c_lst **lst)
{
	t_c_lst	*ptr;

	ptr = (*lst);
	while (ptr)
	{
		ptr = (*lst)->next;
		close((*lst)->fd);
		free(*lst);
		(*lst) = NULL;
		(*lst) = ptr;
	}
}

void			save_close_openfds(int fd, int mode)
{
	static	t_c_lst		*lst = NULL;

	if (mode == 1)
		create_fd_save(fd, &lst);
	else
	{
		del_fd_save(&lst);
		lst = NULL;
	}
}
