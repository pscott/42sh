#include "libft.h"
#include "errors.h"
#include "line_editing.h"

/* 
** compare start_actual_word (== len) and first word of the input. if ==, then its first arg of input
*/

static int			is_first_arg_and_exec(char *str, unsigned int cursor_pos, unsigned int start_actual_word)
{
	unsigned int	i;

	i = 0;

	if (cursor_pos == 0)
		return (2);//space
	else
		cursor_pos--;
	while (str && is_white_spaces(str[i]) && i <= cursor_pos)
		i++;
	if (i < start_actual_word)//je suis pas sur le premier mot
			return (0);
	else//je suis sur le premier mot
	{
		if (str[cursor_pos] == '\0' || is_white_spaces(str[cursor_pos]))
			return (2);
		else if (str[i] == '~' && (str[i + 1] == '/'))
				return (6);
		else if (str[i] == '$')
			return (5);
		else
			return (3);
	}
}

static char			*handle_x_arg(char *input, char *to_find_and_next_char)
{
	char			*path;
	char			*to_find;
	char			*tmp;
	char			*tmp2;
	char			*ret_str;
	t_auto_comp		*match;

	to_find = NULL;
	path = NULL;
	ret_str = NULL;
	match = NULL;
	tmp = NULL;
	tmp2 = NULL;

	if (input && input[0] && ft_strchr(input, '/'))
		tmp = ft_strndup(input, ft_strlen(input) - ft_strlen(ft_strrchr(input, '/') + 1));
	get_path_file_and_to_find(input, &path, &to_find);
	if (!to_find[0] || is_white_spaces(to_find[0]))
		find_all_except_dots(path, &match); 
	else
		find_all_match(path, &match, to_find, to_find_and_next_char);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	tmp2 = ft_strjoin(tmp, ret_str);
	if (path)
		ft_strdel(&path);
	if (to_find)
		ft_strdel(&to_find);
	ft_strdel(&ret_str);
	return (tmp2);
}

char				*handle_first_arg_dot_tilde(int type, char *to_find)
{
	char			*ret;

	ret = NULL;
	if (type == 1)//case . / .. en premier arg ou ~ 
	{
		if ((!ft_strcmp(to_find, ".") || !ft_strcmp(to_find, "..")) && !(ret = ft_strjoin(to_find, "/")))
			ERROR_MEM
	//ret = search_dirs_and_exe(to_find_full + start_actual_word, len - start_actual_word);//chercher doss ET exec MEME CACHES dans path specifie. comme quand ca finde pas un exe en first + EXE. si . ou .., on append direct un slash et on display dossiers et exec meme caches du dossier. si /, on affiche la liste des dossiers (append /) et des executables
	}
	else if (type == 6)// case ~/ 
		ret = home_directory_first_arg(to_find);
	return (ret);
}

static char			*handle_first_bin(t_vars *vars, char *to_find, char *str, unsigned int len)
{
	char			*ret;

	ret = NULL;
	if (!(ret = new_auto_completion_bin(vars, to_find, str, len)))
	{
		if (!ft_strncmp(to_find, ".", 2) || !ft_strncmp(to_find, "..", 3))
		{
			if (!(ret = ft_strjoin(to_find, "/")))
				ERROR_MEM
		}
		else if (!ft_strchr(to_find, '/'))
			ret = search_dirs_first_arg(".", to_find, len);//chercher tous les dossiers dans le path specifie en to_find + start_actual_word, si first arg et pas exec. si match, append / // ADAPTER POUR LE CAS OU SRCS/ ...
		else
			ret = search_dirs_and_exe(to_find, len);
	}
	return (ret);
}

static int			format_finding_and_get_correct_ret(char **ret, int start_actual_word, char *input, unsigned int len)
{
	char			*save;
	char			*tmp;

	save = NULL;
	tmp = NULL;
	if (!(save = ft_strndup(input, start_actual_word)))
		ERROR_MEM
	if (!(*ret))
	{
		if (!((*ret) = ft_strndup(input, len)))
			ERROR_MEM
	}
	else
	{
		if (save)
		{
			if (!(tmp = ft_strjoin(save,(*ret))))
				ERROR_MEM
			ft_strdel(ret);
		}
		if (!((*ret) = ft_strdup(tmp)))
			ERROR_MEM
		ft_strdel(&tmp);
	}
	ft_strdel(&save);
	return (0);
}

char				*new_auto_completion(char *input, unsigned int len, t_vars *vars)
{
	char			*to_find_full;
	char			*ret;
	char			*tmp;
	char			*str;
	int				start_actual_word;

	//++ handler DOLLAR
	ret = NULL;
	tmp = NULL;
	if (!input)
		return (NULL);
	start_actual_word = get_needed_values(input, len, &str, &to_find_full);
	if (is_first_arg_and_exec(input, len, start_actual_word) == 3)
		ret = handle_first_bin(vars, to_find_full + start_actual_word, str + start_actual_word, len);
	else if (is_first_arg_and_exec(input, len, start_actual_word) == 2)//case white sapce en premier arg
		new_auto_completion_space(vars);//jsute display tous les execs et variables, on returne une dup de input
	else if (is_first_arg_and_exec(input, len, start_actual_word))
		ret = handle_first_arg_dot_tilde(is_first_arg_and_exec(input, len, start_actual_word), to_find_full + start_actual_word);

	else if (!is_first_arg_and_exec(input, len, start_actual_word))
		ret = handle_x_arg(to_find_full + start_actual_word, str + start_actual_word);
	format_finding_and_get_correct_ret(&ret, start_actual_word, input, len);
/*	
ft_printf("\nret : |%s|, input |%s|, ret_len = |%d|, input_len = |%d|\n", ret, input, ft_strlen(ret), len);
sleep(1);
*/
	ft_strdel(&to_find_full);
	ft_strdel(&str);
	return (ret);
}
