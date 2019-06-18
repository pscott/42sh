#include "ftsh.h"
#include "history.h"

static int		is_fc(const char *s)
{
	if (s && (ft_strstr(s, "fc")))
	{
		if (!ft_strstr(s, "-l"))
			return (0);
		return (1);
	}
	return (0);
}

t_hist_lst		*insert_left(t_hist_lst *hist_lst, const char *line, char keep)
{
	t_hist_lst	*probe;
	t_hist_lst	*insert;

//	if (is_fc(line))
//		return (NULL);
	if (!(insert = create_hist_lst(line, keep)))
		return (NULL);
	if (!(probe = hist_lst))
		return (insert);
	else
	{
		if (probe->prev)
		{
			probe->prev->next = insert;
			insert->prev = probe->prev;
		}
		insert->next = probe;
		probe->prev = insert;
	}
	return (insert);
}

t_hist_lst		*insert_right(t_hist_lst *hist_lst, const char *line, char keep)
{
	t_hist_lst	*probe;
	t_hist_lst	*insert;

	if (!(insert = create_hist_lst(line, keep)))
		return (NULL);
	if (!(probe = hist_lst))
		return (insert);
	else
	{
		if (probe->next)
		{
			probe->next->prev = insert;
			insert->next = probe->next;
		}
		probe->next = insert;
		insert->prev = probe;
	}
	return (insert);
}
