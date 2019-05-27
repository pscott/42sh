#include "libft.h"
#include "line_editing.h"

static void				get_user_name(char **users, const char *line)
{
	char				*tmp;
	char				*tmp2;
	struct passwd		*infos;
	struct stat			file_infos;

	tmp = NULL;
	tmp2 = NULL;
	infos = NULL;
	if (!(tmp = ft_strndup(line, ft_strlen_char(line, ':'))))
		ERROR_MEM
			if (!(tmp2 = ft_strjoin("~", tmp)))
				ERROR_MEM
					infos = getpwnam(tmp);
	if ((stat(infos->pw_dir, &file_infos) != -1))
	{
		if (S_ISDIR(file_infos.st_mode))
		{
			if (!((*users) = ft_strjoin(tmp2, "/")))
				ERROR_MEM
		}
	}
	else if (!(*users = ft_strdup(tmp2)))
		ERROR_MEM
			free_two_strings(&tmp, &tmp2);
}

static int			get_users_list(t_auto_comp **match, const char *to_find)
{
	int				fd;
	char			*line;
	int				ret;
	char			*users;
	char			*tmp;

	line = NULL;
	users = NULL;
	tmp = NULL;
	fd = open("/etc/passwd", 0);
	while (((ret = get_next_line_2(fd, &line)) != -1))
	{
		if (line && line[0] && line[0] != '#' && (!to_find[0] || !strncmp(to_find, line, ft_strlen(to_find))))
		{
			get_user_name(&users, line);
			if (users == NULL)
				users = ft_strnew(1);
			create_match_link(match, users);
			ft_strdel(&users);
		}
		if (!ret)
			break ;
	}
	return (0);
}

char				*users_passwd(const char *to_find)
{
	t_auto_comp		*match;
	char			*str;
	char			*ret_str;

	match = NULL;
	ret_str = NULL;
	str = NULL;
	if (ft_strlen(to_find) > 1)
	{
		if (!(str = ft_strdup(to_find + 1)))
			ERROR_MEM
	}
	else
	{
		if (!(str = ft_strnew(1)))
			ERROR_MEM
	}
	get_users_list(&match, str);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	ft_strdel(&str);
	return (ret_str);
}