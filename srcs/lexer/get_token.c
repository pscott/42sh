#include "ftsh.h"
#include "lexer.h"
#include "input.h"

//TODO is double pointer necesary ?
static t_token	*trim_escaped_newline(t_st_cmd **st_cmd)
{
	*st_cmd = get_st_cmd(NULL);
	(*st_cmd)->st_txt->data_size -= 2;
	ft_bzero(&(*st_cmd)->st_txt->txt[(*st_cmd)->st_txt->data_size], 2);
	return (NULL);
}

static t_token	*get_dquot_token(char **cmdline)
{
	t_token			*token;
	t_st_cmd	*st_cmd;
	size_t			i;

	i = 1;
	while ((*cmdline)[i] != 0 && (*cmdline)[i] != '"')
	{
		if ((*cmdline)[i] == '\\')
		{
		   	if ((*cmdline)[i + 1] == '\"')
				i++;
			else if ((*cmdline)[i + 1] == '\n')//TODO check me
				return (trim_escaped_newline(&st_cmd));
		}
		i++;
	}
	if ((*cmdline)[i] == 0)
		return (NULL);
	if (!(token = create_token(*cmdline, ++i, tk_dq_str)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_squot_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((*cmdline)[i] && (*cmdline)[i] != '\'')
		i++;
	if ((*cmdline)[i] == 0)
		return (NULL);
	if (!(token = create_token(*cmdline, ++i, tk_sq_str)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_regular_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	//TODO check unwanted char in this func or in ft_is_metachar()
	i = 0;
	while ((*cmdline)[i] && !ft_is_metachar((*cmdline)[i]))
	{
		if ((*cmdline)[i] == '$' && i != 0)
			break ;
		i++;
	}
	if (!(token = create_token(*cmdline, i, tk_word)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_monochar(char **cmdline)
{
	t_token			*token;
	t_st_cmd		*st_cmd;

	if (*(*cmdline + 1) == '\n')
	{
		st_cmd = get_st_cmd(NULL);//make func ? i did it 'trim_escaped_newline()//TODO need free
		st_cmd->st_txt->data_size -= 2;
		ft_bzero(&st_cmd->st_txt->txt[st_cmd->st_txt->data_size], 2);
		return (NULL);
	}
	(*cmdline)++;
	if (!(token = create_token(*cmdline, 1, tk_monoc)))
		ERROR_MEM;
	(*cmdline)++;
	return (token);
}

static t_token	*get_eat_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (ft_is_white_space((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, tk_eat)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

//just make a tk_word, parse_dollars() will do the rest
static t_token	*check_param_sub_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while ((*cmdline)[i] && (*cmdline)[i] != '}')
		i++;
	if ((*cmdline)[i] == 0)
	{
		ft_printf("TMP: NO '}' found\n");
		return (NULL);//=cont_read
	}
	i++;//test
	if (!(token = create_token(*cmdline, i, tk_word)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);//tmp
}

static void		modif_ints(unsigned int *braces_count, int braces_to_add
				, int *i, int i_to_add)
{
	*braces_count += braces_to_add;
	*i += i_to_add;
}

//Make a tk_word
static t_token	*check_arith_exp_token(char **cmdline)
{
	unsigned int	braces_count;
	int				i;
	t_token			*token;

	braces_count = 0;
	i = -1;
	while((*cmdline)[++i])
	{
		if (!ft_strncmp("$((", (*cmdline) + i, 3))
			modif_ints(&braces_count, 1, &i, 2);
		else if (!ft_strncmp("))", (*cmdline) + i, 2))
		{
			modif_ints(&braces_count, -1, &i, 1);
			if (braces_count == 0)
			{
				i++;
				break ;
			}
		}
	}
	if (braces_count == 0)
		token = create_token(*cmdline, i, tk_word);
	else
		return (NULL);
	*cmdline = *cmdline + i;
	return (token);
}


/*
** get_token
** return a malloced token accordingly to the character under the cmdline
** pointer
** all sub get_token functions move the cmdline pointer accordingly
** and return NULL when they fail to get the token, so lexer send LEX_CONT_READ
** to handle_input
*/

t_token			*get_token(char **cmdline, t_operation *op_chart)
{
	t_token	*token;

	if (**cmdline == '"')
		return (get_dquot_token(cmdline));
	else if (**cmdline == '\'')
		return (get_squot_token(cmdline));
	else if (**cmdline == '\\')
		return (get_monochar(cmdline));
	else if (ft_is_white_space(**cmdline))
		return (get_eat_token(cmdline));
	else if ((ft_strlen(*cmdline) > 3) && !ft_strncmp(*cmdline, "$((", 3))
		return (check_arith_exp_token(cmdline));
	else if ((ft_strlen(*cmdline) > 2) && !ft_strncmp(*cmdline, "${", 2))
		return (check_param_sub_token(cmdline));
	else if ((token = get_op_chart_token(cmdline, op_chart)))
		return (token);
	else
		return (get_regular_token(cmdline));
}
