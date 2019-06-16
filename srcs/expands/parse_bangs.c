#include "lexer.h"
#include "env.h"
#include "ast.h"
#include "line_editing.h"
#include "cmd_parsing.h"
#include "history.h"

int				case_bangbang(t_st_cmd *st_cmd, char **str, int *i)
{
	char		*insert;
	size_t		len;
	size_t		index[2];
	
	insert = st_cmd->hist_lst->prev->txt;
	len = ft_strlen_char(insert, '\n');
	if (!(insert = ft_strndup(insert, len)))
		clean_exit(1, 1);
	index[0] = *i;
	index[1] = ++(*i);
	substitute_slice(str, index, insert);
	free(insert);
	return (0);
}

int				case_minus(t_st_cmd *st_cmd, char **str, int *i)
{
	t_hist_lst	*insert;
	char		*pattern;
	size_t		len;
	size_t		index[2];
	int			nb;
	
	nb = ft_atoi(&(*str[*i + 1]));
				ft_dprintf(2, "{{%d}}", nb);
	insert = get_entry_lst(st_cmd->hist_lst, *st_cmd->hist_len + nb); 
	len = ft_strlen_char(insert->txt, '\n');
	if (!(pattern = ft_strndup(insert->txt, len)))
		clean_exit(1, 1);
	index[0] = *i;
	index[1] = len;
	substitute_slice(str, index, pattern);
	++(*i);
	while ((nb = nb / 10))
		++(*i);
	return (0);
}

static int		replace_bang(char **str)
{
	int			i;
	t_st_cmd	*st_cmd;

	i = 0;
	st_cmd = get_st_cmd(NULL);
	while ((*str)[i])
	{
		if ((*str)[i] == '!' && (*str)[i + 1])
		{
			if ((*str)[i + 1] == '!')
			{
				ft_dprintf(2, "YLO");
				case_bangbang(st_cmd, str, &i);
			}
			
			else if ((*str)[i + 1] == '-') 
			{
				case_minus(st_cmd, str, &i);
			}
			/*
			else if (ft_isdigit(*str[i + 1])) 
				case_nb(st_cmd, str, &i);
			else
				case_word(st_cmd, str, &i);
				*/
		}
		i++;
	}
	//replace str dans st_cmd
	return (0);
}

int				parse_bangs(t_token *token_head)
{
	t_token			*prev_token;
	t_token			*curr_token;
	int				ret;

	curr_token = token_head;
	prev_token = NULL;
	while (curr_token)
	{
		if (curr_token->type == tk_word && ft_strchr(curr_token->content, '!'))//tk_dqstr 
		{
			ret = replace_bang(&curr_token->content);
			return (0);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	return (1);
}
