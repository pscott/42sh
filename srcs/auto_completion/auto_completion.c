#include "libft.h"
#include "errors.h"
#include "line_editing.h"
#include <dirent.h>

/* 
** compare start_actual_word (== len) and first word of the input. if ==, then its first arg of input
*/

static int			is_first_arg_and_exec(char *str, unsigned len)
{
	unsigned int	i;

	i = 0;
	while (str[i] && is_white_spaces(str[i]) && i <= len)
		i++;
	if (i == len)//first arg
	{
		if (str && (str[i] == '/' || str[i] == '.' || str[i] == '~'))//file ou exec?
			return (1);//FILE, relative ou absolute en FIRST ARG --> apprend / si . ou .. , chercher dossiers et exec en relatif. si / ou .. ou . alors chercher uniquement dosser et exec aussi !!!
		else if (str && (str[i] == ' ' || str[i] == '\0'))
			return (2);//FULL WHITE SPACES && "first arg" tout chercher
		else
			return (3);//Exec && first arg
	}
	else
		return (0);
}

static int			handle_not_first_arg(char *str, char *to_find_and_next_char, unsigned int len)
{

	if (str && (str[len] == '/' || str[len] == '.' || str[len] == '~'))//file ?
			return ((int)str[len] + 10);//cherher TOUT en relatif. si slash, tout. si ., fichiers caches + . et .. dans dossier courant, si .., append slash et ALL search
	//	else
		//	handle_second_arg
			return (6);//file & second arg
	return (0);
}


static int			new_auto_completion_file(char *str, unsigned int len)
{
/*	char			*to_find;
	char			*path_file;
	t_auto_comp		*match;

	match = NULL;
	if (!(to_find = get_to_find_file(str)))
		return (ERR_MALLOC);
	if (!(path_file = get_path_file(str, &to_find)))
	{
		ft_strdel(&to_find);
		return (ERR_MALLOC);
	}
	if (find_matching_exe(&path_file, &match, to_find, 0))	
	{
		ft_strdel(&to_find);
		ft_strdel(&path_file);
		return (ERR_MALLOC);
	}
	if (!to_find)
		if (!(to_find = ft_strnew(1)))
		{
			ft_strdel(&to_find);
			ft_strdel(&path_file);
			return (ERR_MALLOC);
		}
	if (match)
		get_ret_or_display_matches(match, to_find, len);
	ft_strdel(&path_file);
	ft_strdel(&to_find);*/
	return (0);
}

static char			*new_auto_completion_bin(t_vars *vars, char *str, char *to_find_and_next_char, unsigned int len)
{
	char			**path;
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;
	int				i;

	match = NULL;
	ret_str = NULL;
	i = -1;
	path = NULL;
	if (get_path(&path, vars))//recup le path
		ERROR_MEM
	if (!(to_find = ft_strdup(str)))
		ERROR_MEM
	if (find_matching_exe(path, &match, to_find, to_find_and_next_char))//stock dans match les noms correspondants
		ERROR_MEM
	ft_free_ntab(path);
	if (match)
	{
		ret_str = get_ret_or_display_matches(match, to_find, len);//chercher alias
	}
//	if (!ret_str)
//		ret_str = ft_strdup(to_find); il faut chercher dossiers et exec dans dossier courant
//	ft_strdel(&to_find);
	return (ret_str);
}

int					find_matching_dirs(char *directory, t_auto_comp **match, char * to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);//ERR_OPENDIR
	while ((ent = readdir(dir)))
	{
		if (!compare_entry(to_find, ent->d_name))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
			{
				tmp = NULL;
				tmp = ft_strjoin(ent->d_name, "/");
				ft_putendl(tmp);//
				sleep(1);//
				if (create_match_link(match, tmp, -1))
				{
					closedir(dir);
					return (1);//ERR MALL
				}
			}
		}
	}
	if (closedir(dir) == -1)
		return (1);//ERR_CLOSEDIR;
	return (0);
}

char				*search_dirs_first_arg(char *directory, char *str, int len)
{
	t_auto_comp		*match;
	char			*ret_str;
	char			*to_find;

	match = NULL;
	ret_str = NULL;
	if (!(to_find = ft_strdup(str)))
		ERROR_MEM
	if (find_matching_dirs(directory, &match, to_find))//je fais la liste de match avec / append
		ERROR_MEM
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, len);
	ft_strdel(&to_find);
	return (ret_str);
}


int					find_matching_dirs_and_exe_even_hidden(char *directory, t_auto_comp **match, char * to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);//ERR_OPENDIR
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		if (!compare_entry(to_find, ent->d_name))
		{
			if (access(ent->d_name, X_OK) == 0) 
			{
				if (ent->d_type && ent->d_type == DT_DIR)
					tmp = ft_strjoin(ent->d_name, "/");
				else
					tmp = ft_strdup(ent->d_name);
				if (create_match_link(match, tmp, -1))
				{
					closedir(dir);
					return (1);//ERR MALL
				}
				ft_strdel(&tmp);
			}
		}
	}
	if (closedir(dir) == -1)
		return (1);//ERR_CLOSEDIR;
	return (0);
}

char				*search_dirs_and_exe(char *str, int len)
{
	char			*ret_str;
	char			*ret_tmp;
	char			*to_find;
	char			*path;
	t_auto_comp		*match;

	ret_str = NULL;
	ret_tmp = NULL;
	path = NULL;
	match = NULL;
	if (ft_strlen(str) < 3 && (str[0] == '.' && (str[1] == '.' || str[1] == '\0')))
	{
		if (!(ret_str = ft_strjoin(str, "/")))
			ERROR_MEM
		return (ret_str);
	}
	else
	{
		if ((to_find = ft_strrchr(str, '/') + 1))
		{
			if (!(path = ft_strndup(str, ft_strlen(str) - ft_strlen(to_find))))
				ERROR_MEM
		}
		else
			if (!(path = ft_strdup(str)))
				ERROR_MEM
		if (find_matching_dirs_and_exe_even_hidden(path, &match, to_find))
			ERROR_MEM
		if (match)
		{
			while (match->prev)
				match = match->prev;
			ret_tmp = get_ret_or_display_matches(match, to_find, len - ft_strlen(path));
			if (!(ret_str = ft_strjoin(path, ret_tmp)))
				ERROR_MEM
		}
	}
	return (ret_str);

}

int				get_everything_from_path(char *path, t_auto_comp **match)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(path)) == NULL)
		return (1);
	while ((ent = readdir(dir)))
	{
		if (ft_strncmp(ent->d_name, "..", 2) && ft_strncmp(ent->d_name, ".", 1))
		{
			tmp = ft_strdup(ent->d_name);
			if (create_match_link(match, tmp, -1))
			{
				closedir(dir);
				return(1);//ERRCLOSEDI
			}
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return(1);//err closdire
	return (0);

}

int				find_exe_space(char **path, t_auto_comp **match)
{
	int			i;
	char		*true_path;

	true_path = NULL;
	i = 0;
	while (path[i])
	{
		true_path = rm_spaces_path(path[i++]);
		get_everything_from_path(true_path, match);
	}
	return (0);
}

int				find_all_var_and_exe(char **path, t_auto_comp **match)
{
	if (find_exe_space(path, match))
		ERROR_MEM
/*	if (find_alias_space(match)
		ERROR_MEM
	if (find_reserved_words_space(match)
		ERROR_MEM*/
	return (0);
}

char			*new_auto_completion_space(t_vars *vars)
{
	char			**path;
	t_auto_comp		*match;

	path = NULL;
	match = NULL;
	if (get_path(&path, vars))//recup le path
		ERROR_MEM
	if (find_all_var_and_exe(path, &match))//stock dans match les noms correspondants
		ERROR_MEM
	ft_free_ntab(path);
	if (match)
	{
		ft_putendl(match->name);
		sleep(1);
		get_ret_or_display_matches(match, NULL, 0);
	}
//	if (!ret_str)
//		ret_str = ft_strdup(to_find); il faut chercher dossiers et exec dans dossier courant
//	ft_strdel(&to_find);
	return (NULL);
}

char				*new_auto_completion(char *input, unsigned int len, t_vars *vars)
{
	char			*to_find_full;
	char			*ret;
	char			*tmp;
	char			*str;
	int				start_actual_word;
	char			*str_save_begin;

	//++ handler DOLLAR
	ret = NULL;
	str_save_begin = NULL;
	if (!input)
		return (NULL);
	start_actual_word = get_needed_values(input, len, &str, &to_find_full);
	if (!(str_save_begin = ft_strndup(input, start_actual_word)))
		ERROR_MEM
	if (is_first_arg_and_exec(input, start_actual_word) == 3)
	{
	//	ft_printf("to_find + start :|%s|, str + start :|%s|", to_find_full + start_actual_word, str+start_actual_word);
		if (!(ret = new_auto_completion_bin(vars, to_find_full + start_actual_word, str + start_actual_word, len - start_actual_word)))
			ret = search_dirs_first_arg(".", to_find_full + start_actual_word, len - start_actual_word);//chercher tous les dossiers dans le path specifie en to_find + start_actual_word, si first arg et pas exec. si match, append /
	}
	else if (is_first_arg_and_exec(input, start_actual_word) == 1)//case . / .. en premier arg ou ~ 
	{
		ret = search_dirs_and_exe(to_find_full + start_actual_word, len - start_actual_word);//chercher doss ET exec MEME CACHES dans path specifie. comme quand ca finde pas un exe en first + EXE. si . ou .., on append direct un slash et on display dossiers et exec meme caches du dossier. si /, on affiche la liste des dossiers (append /) et des executables
	}
	else if (is_first_arg_and_exec(input, len) == 2)//case white sapce en premier arg
		new_auto_completion_space(vars);//jsute display tous les execs et variables, on returne une dup de input
	/*
	else if (!is_first_arg_and_exe(input, len))
		ret = handle_not_first_arg(vars, to_find_full + start_actual_word, str + start_actual_word, len - start_actual_word);


	else if (is_first_arg_and_exec(input, len) == 6)//case file en xx arg. si dossier non specifie, alors tout dans repertoire courrant (sauf . et ..), en appendant / a la fin des dossiers. 
		new_auto_completion_file();
*/
/*	else
	{
		if (new_auto_completion_file(str, len))
			return (ERR_MALLOC);
	}
*/	
	if (!ret)
		ret = ft_strndup(input, len);
	else
	{
		tmp = ft_strjoin(str_save_begin, ret);
		ret = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
//ft_printf("ret : |%s|\n", ret);
//sleep(2);
//	ft_strdel(&to_find_full);
	return (ret);
}
