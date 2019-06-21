#include "auto_completion.h"
#include "cmd_parsing.h"

static int	is_not_dollarized_char(char *s, int i, char c)
{
	if (s[i] == c && (!i || s[i - 1] != '$'))
		return (1);
	return (0);
}

static int	is_glob_needed(char *s)
{
	int		i;
	int		j;

	i = -1;
	while (s[++i])
	{
		if (ft_is_quote(s[i]))
		{
			j = i + 1;
			while (s[i] != s[j])
				j++;
			i = j;
		}
		if (s[i] == '$' && s[i + 1] == '*')
			i += 2;
		if (is_not_dollarized_char(s, i, '*') || is_not_dollarized_char(s, i, '?')
			|| (i > 1 && is_not_dollarized_char(s, i, '?') && s[i - 2] == '$'))
			return (1);
	}
	return (0);
}

int			get_dir(t_st_dir *st_dir, char *str)
{
	get_path_file_and_to_find((const char*)str, &st_dir->path, &st_dir->to_find);
	if ((st_dir->dir = opendir(st_dir->path)) == NULL)
	{
		free_two_strings(&st_dir->path, &st_dir->to_find);
		return (-1);
	}
	return (0);

}

char		*create_string(t_st_glob *st_glob, int len)
{
	char	*ret;
	char	*tmp;
	char	*app;

	while (st_glob->prev)
		st_glob = st_glob->prev;
	tmp = NULL;
	ret = NULL;
	while (st_glob)
	{
		if (st_glob->keep == 1)
		{
			if (!ret)
				ret = ft_strdup(st_glob->name);
			else
			{
				app = ft_strjoin(ret, " ");
				tmp = ft_strjoin(app, st_glob->name);
				ft_strdel(&ret);
				ft_strdel(&app);
				ret = ft_strdup(tmp); 
				ft_strdel(&tmp);
			}
		}
		st_glob = st_glob->next;
	}
	return (ret);
}

char		*from_list_to_string(t_st_glob *st_glob, t_st_dir *st_dir)
{
	t_st_glob	*first;
	int			min;
	int			len;

	while (st_glob->prev)
		st_glob = st_glob->prev;
	first = st_glob;
	min = first->match;
	while ((first = first->next))
	{
		min = ft_min(min, first->match);
	ft_dprintf(2, "in min||%s||%d\n", first->name, min);
	}
	len = 0;
	while (first)
	{

		if (first->match == min/* && !ft_strncmp(st_dir->to_find, first->name, min + 1)*/)
		{
			first->keep = 1;
			len += ft_strlen(first->name) + 1;
		}
		first = first->prev;
	}
	return (create_string(st_glob, len));
}

char		*globing(char *str)
{
//handle [*]
	t_st_glob	*st_glob;
	t_st_dir	*st_dir;
	int			ret;
	char		*matchs;			
	int			ok;


	if (!(st_glob = (t_st_glob *)malloc(sizeof(t_st_glob))))
		clean_exit(1, 1);
	st_glob = NULL;
	if (!(st_dir = (t_st_dir *)malloc(sizeof(t_st_dir))))
		clean_exit(1, 1);
	if ((get_dir(st_dir, str)) == -1)
		return (NULL);
	ok = 0;
	while ((st_dir->current = readdir(st_dir->dir)) != NULL)
	//	&& ft_strncmp(st_dir->current->d_name, "..", 3)
	//	&& ft_strncmp(st_dir->current->d_name, ".", 2))
	{
		ret = find_matchs(st_dir);
		if (ret >= 0)//except case !
		{
	ft_dprintf(2, "\n\||%s||%d\n", st_dir->current->d_name, ret);
			ok = 1;
			create_match_link_glob(&st_glob, st_dir->current->d_name, ret);
		}	
	}
	if (st_glob)
		matchs = from_list_to_string(st_glob, st_dir);
	if ((closedir(st_dir->dir)) == -1)
	{
		free(st_dir->to_find);
		return (NULL);
	}
	/*
	ft_dprintf(2, "to_find %s et path %s", st_dir->to_find, st_dir->path);
	sleep(2);
	*/
	/*
	ft_dprintf(2, "----------------\n");


	while (st_glob)
	{
		ft_dprintf(2, st_glob->name);
		st_glob = st_glob->next;
	}
	ft_dprintf(2, "----------------\n");
*/
	return (NULL);//lst to str
}

char		*expand_filename(char *str)
{
	char	*ret;
	char	*glob;

	if (!(ret = ft_strnew(0)))
		clean_exit(1, 1);
	glob = globing(str);

	return (ret);
}

int			filename_exp(char **str)
{
	char	*tmp;


//	if (!(is_glob_needed(*str)))
//		return (0);
	tmp = expand_filename(*str);
	
	return (0);


}
