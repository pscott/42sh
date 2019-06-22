#include "libterm.h"
#include "cursor.h"

static void		fill_res(char ***res)
{
	if (!((*res)[0] = ft_strdup(BEGIN_LINE))
		|| !((*res)[1] = ft_strdup(INVISIBLE))
		|| !((*res)[2] = ft_strdup(VISIBLE))
		|| !((*res)[3] = ft_strdup(CLEAR))
		|| !((*res)[4] = ft_strdup(CLEAR_BELOW))
		|| !((*res)[5] = ft_strdup(MOVE_DOWN))
		|| !((*res)[6] = ft_strdup(ERASE_ENDLINE))
		|| !((*res)[7] = ft_strdup(HIGHLIGHT))
		|| !((*res)[8] = ft_strdup(NO_HIGHLIGHT))
		|| !((*res)[9] = ft_strdup(SCROLL_DOWN))
		|| !((*res)[10] = ft_strdup(MOVE_UP))
		|| !((*res)[11] = ft_strdup(MOVE_RIGHT))
		|| !((*res)[12] = ft_strdup(MOVE_LEFT)))
	{
		ft_free_ntab(*res);
		*res = NULL;
	}
}

static char		**create_cap_array(void)
{
	char	**res;

	if (!(res = (char**)malloc(sizeof(*res) * (NUM_CAPS + 1))))
		return (NULL);
	ft_bzero(res, sizeof(*res) * (NUM_CAPS + 1));
	fill_res(&res);
	return (res);
}

int				check_caps(void)
{
	char	**caps;
	int		i;

	if (!(caps = create_cap_array()))
	{
		write(2, "error: failed to allocate memory\n", 33);
		exit(1);
	}
	i = 0;
	while (i < NUM_CAPS)
	{
		if (tgetstr(caps[i], NULL) == NULL)
		{
			ft_free_ntab(caps);
			return (0);
		}
		i++;
	}
	ft_free_ntab(caps);
	return (1);
}
