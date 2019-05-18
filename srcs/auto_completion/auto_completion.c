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
	unsigned int	k;

	i = 0;
	while (str[i] && is_white_spaces(str[i]) && i <= len)
		i++;
	if (i == len)//first arg
	{
		if (str && (str[i] == ' ' || str[i] == '\0'))
			return (2);//FULL WHITE SPACES && "first arg" tout chercher
		else
			return (3);//Exec && first arg && append / a . ou ..
	}
	else
		return (0);
}

int					find_all_except_dots(char *directory, t_auto_comp **match)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (print_errors(ERR_OPENDIR, ERR_OPENDIR_STR, NULL));
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		if (ft_strncmp("..", ent->d_name, 3) && ft_strncmp(".", ent->d_name, 2))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
				tmp = ft_strjoin(ent->d_name, "/");
			else
				tmp = ft_strjoin(ent->d_name, " ");
			if (!tmp)
				ERROR_MEM
		/*			ft_putendl(tmp);
					sleep(1);*/
			if (create_match_link(match, tmp, -1))
			{
				closedir(dir);
				return (1);//ERR MALL
			}
		//	ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (print_errors(ERR_CLOSEDIR, ERR_CLOSEDIR_STR, NULL));
	return (0);
}


int					find_all_match(char *directory, t_auto_comp **match, char *to_find, char *next)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (print_errors(ERR_OPENDIR, ERR_OPENDIR_STR, NULL));
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		if (!(compare_entry(to_find, ent->d_name)))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
				tmp = ft_strjoin(ent->d_name, "/");
			else if (is_white_spaces(next[ft_strlen(to_find)]) || !next[ft_strlen(to_find)])
				tmp = ft_strjoin(ent->d_name, " ");
			else
				tmp = ft_strdup(ent->d_name);
			if (!tmp)
				ERROR_MEM
				/*	ft_putendl(tmp);
					sleep(1);*/
			if (create_match_link(match, tmp, -1))
				ERROR_MEM
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (print_errors(ERR_CLOSEDIR, ERR_CLOSEDIR_STR, NULL));
	return (0);
}

int					slash_counter(const char *s)
{
	int				i;
	int				count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == '/')
		{
			count++;
			while (s[i] == '/')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char			*handle_x_arg(t_vars *vars, char *input, char *to_find_and_next_char, unsigned int len)
{
	char			*path;
	char			*to_find;
	char			*tmp;
	char			*tmp2;
	char			*ret_str;
	t_auto_comp		*match;
	int				i;

	to_find = NULL;
	path = NULL;
	ret_str = NULL;
	match = NULL;
	tmp = NULL;
	tmp2 = NULL;

	/*
	ft_printf("input |%s|", input);
	sleep(1);
*/
	if (input && input[0] && ft_strchr(input, '/'))
		tmp = ft_strndup(input, ft_strlen(input) - ft_strlen(ft_strrchr(input, '/') + 1));
	get_path_file_and_to_find(input, &path, &to_find);
	
			ft_putendl(input);
			ft_putendl(path);
			ft_putendl(to_find);
			sleep(1);
		if (!to_find[0] || is_white_spaces(to_find[0]))
			find_all_except_dots(path, &match); 
		
		else
		{
			find_all_match(path, &match, to_find, to_find_and_next_char);
		}
			
	//	ft_printf("|%s|", to_find);
	//	sleep(1);
		

		ret_str = get_ret_or_display_matches(match, to_find, len);
		ft_printf("{{%s}}\n", ret_str);
		sleep(1);
		tmp2 = ft_strjoin(tmp, ret_str);
		
/*		while (match->prev)
			match = match->prev;
		ft_putendl(match->name);
		sleep(2);
*/
/*	else
	{
		if (slash_counter(to_find) == 1)
			find_all_except_dots(path, &match);
		else
			find_all_match(path,, &match, to_find, to_find_and_next_char);
	}
	if (match)
	{
	}
*/	 return (tmp2);
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
			/*
			ft_printf("save:|%s|", str_save_begin);
	sleep(2);
*/
	if (is_first_arg_and_exec(input, start_actual_word) == 3)
	{
		if (!(ret = new_auto_completion_bin(vars, to_find_full + start_actual_word, str + start_actual_word, len - start_actual_word)))
		{
			if (!ft_strncmp(to_find_full + start_actual_word, ".", 2) || !ft_strncmp(to_find_full + start_actual_word, "..", 3))
			{
				if (!(ret = ft_strjoin(to_find_full + start_actual_word, "/")))
					ERROR_MEM
			}
			else if (!ft_strchr(to_find_full + start_actual_word, '/'))
				ret = search_dirs_first_arg(".", to_find_full + start_actual_word, len - start_actual_word);//chercher tous les dossiers dans le path specifie en to_find + start_actual_word, si first arg et pas exec. si match, append / // ADAPTER POUR LE CAS OU SRCS/ ...
			else
			{
				ret = search_dirs_and_exe(to_find_full + start_actual_word, len - start_actual_word);
			}
		}
	}
	else if (is_first_arg_and_exec(input, start_actual_word) == 1)//case . / .. en premier arg ou ~ 
	{
		if ((!ft_strcmp(to_find_full + start_actual_word, ".") || !ft_strcmp(to_find_full + start_actual_word, "..")) && !(ret = ft_strjoin(to_find_full + start_actual_word, "/")))
			ERROR_MEM
	//ret = search_dirs_and_exe(to_find_full + start_actual_word, len - start_actual_word);//chercher doss ET exec MEME CACHES dans path specifie. comme quand ca finde pas un exe en first + EXE. si . ou .., on append direct un slash et on display dossiers et exec meme caches du dossier. si /, on affiche la liste des dossiers (append /) et des executables
	}
	else if (is_first_arg_and_exec(input, len) == 2)//case white sapce en premier arg
		new_auto_completion_space(vars);//jsute display tous les execs et variables, on returne une dup de input
	
	else if (!is_first_arg_and_exec(input, len))
	{
		ret = handle_x_arg(vars, to_find_full + start_actual_word, str + start_actual_word, len - start_actual_word);
	}

/*
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
		if (str_save_begin)
		tmp = ft_strjoin(str_save_begin, ret);
		ret = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	
ft_printf("\nret : |%s|\n", ret);
sleep(1);

//	ft_strdel(&to_find_full);
	return (ret);
}
