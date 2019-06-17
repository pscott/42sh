#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

int			fc_display_reverse(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	int				i_curr;
	t_hist_lst		*hist_curr;
	int				diff;

	i_curr = st_fc->i_last;
	diff = *st_cmd->hist_len - st_fc->i_last;
	hist_curr = get_entry_lst(st_cmd->hist_lst, i_curr);
	while (i_curr > 0 && i_curr >= st_fc->i_first)
	{
		if (!(ft_strchr(st_fc->flag, 'n')))
			ft_putnbr(i_curr);
		ft_dprintf(1, "\t%s", hist_curr->txt);
		i_curr--;
		if (hist_curr->prev)
			hist_curr = hist_curr->prev;
	}
	return (0);
}
