#include "libft.h"
#include "errors.h"
#include "line_editing.h"
#define 

static int			get_path(char ***path, t_vars *vars)
{
	char			*tmpath;

	if (!vars || !vars->env_vars)
		return (0);
	if (!(tmpath = get_envline_value("PATH", vars->env_vars)))
	{
		*path = NULL;
		return (0);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		return (ERR_MALLOC);
	return (0);
}

static int			is_first_arg_and_exec(char *str, unsigned len)
{
	int				i;

	i = 0;
	while (str[i + 1] && is_white_spaces(str[i]) && i <= len)
		i++;
	if (i = len + 1)//first arg
	{
		if (str && (str[i] == '/' || str[i] == '.' || str[i] == '~'))//file ou exec?
			return (1);//FILE, relative ou absolute en FIRST ARG --> apprend / si . ou .. , chercher dossiers et exec en relatif. si / ou .. ou . alors chercher uniquement dosser et exec aussi !!!
		else if (str && str[i] == ' ')
			return (2);//FULL WHITE SPACES && "first arg" tout chercher
		else
			return (3);//Exec && first arg
	}
	else
		return (0);
}

static int			handle_not_first_arg(t_vars *vars, char *str, char *to_find_and_next_char, unsigned int len)
{

	if (str && (str[len] == '/' || str[len] == '.' || str[len] == '~'))//file ?
			return ((int)str[len] + 10);//cherher TOUT en relatif. si slash, tout. si ., fichiers caches + . et .. dans dossier courant, si .., append slash et ALL search
		else
			handle
			return (6);//file & second arg
	}
	return (0);
}

static char			*new_auto_completion_bin(t_vars *vars, char *str, char *to_find_and_next_char, unsigned int len)
{
	char			**path;
	char			*to_find_real;
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
	if (find_matching_exe(path, &match, to_find))//stock dans match les noms correspondants
		ERROR_MEM
	ft_free_ntab(path);
	if (match)
	{
		ret_str = get_ret_or_display_matches(match, to_find, len, to_find_and_next_char);
	}
//	if (!ret_str)
//		ret_str = ft_strdup(to_find); il faut chercher dossiers et exec dans dossier courant
//	ft_strdel(&to_find);
//	ft_strdel(&to_find_real);
	return (ret_str);
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

char				*new_auto_completion(char *input, unsigned int len, t_vars *vars)// len +1
{
	char			*to_find_full;
	char			*ret;
	char			*tmp;
	char			*str;
	int				start_actual_word;
	char			*str_save_begin;

	start_actual_word = 0;
	to_find_full = NULL;
	if (!input)
		return (NULL);
	if (!(str = ft_strndup(input, len + 1)))
		ERROR_MEM
	if (!(to_find_full = ft_strndup(input, len)))
		ERROR_MEM
	start_actual_word = len;
//	ft_printf("input : |%s|, str: |%s|, to_find_full : |%s|, start_actual : |%d|, len :|%d|", input, str, to_find_full, start_actual_word, len);
//	sleep(10);
	if (is_white_spaces(to_find_full[len - 1]))
		start_actual_word--;
	while (start_actual_word > 0 && !is_white_spaces(to_find_full[start_actual_word]))
		start_actual_word--;
	if (is_white_spaces(to_find_full[start_actual_word]))
		start_actual_word++;
	if (!(str_save_begin = ft_strndup(input, start_actual_word)))
		ERROR_MEM

	ret = NULL;
	if (is_first_arg_and_exec(input, len) == 3)
	{
		if (!(ret = new_auto_completion_bin(vars, to_find_full + start_actual_word, str + start_actual_word, len - start_actual_word)))
			ret = search_dirs(to_find_full + actual_word, ".");//chercher tous les dossiers dans le dossier courant si first arg et pas exec. si match, append /
	}
	else if (is_first_arg_and_exec(input, len) == 1)//case . / .. en premier arg
		ret = search_dirs_and_exe(to_find_full + start_actual_word);//chercher doc et exec dans path specifie. comme quand ca finde pas un exe en first mais ici le path est specifie. si . ou .., on append direct un slash et on display dossiers et exec meme caches du dossier. si /, on affiche la liste des dossiers (append /) et des executables
	else if (is_first_arg_and_exec(input, len) == 2)//case white sapce en premier arg
		new_auto_completion_bin(vars, "", NULL, NULL);//jsute display tous les execs et variables, on returne une dup de input
}
	else if (!is_first_arg_and_exe(input, len))
		ret = handle_not_first_arg(vars, to_find_fulle + start_actual_word, str + start_actual_word, len - start_actual_word);


	else if (is_first_arg_and_exec(input, len) == 6)//case file en xx arg. si dossier non specifie, alors tout dans repertoire courrant (sauf . et ..), en appendant / a la fin des dossiers. 
		new_auto_completion_file();

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
//	ft_strdel(&to_find_full);
	return (ret);
}
