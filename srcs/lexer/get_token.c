#include "tosh.h"
#include "lexer.h"

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
		   	//if (((*cmdline)[i + 1] == '\'' || (*cmdline)[i + 1] == '\"'))//why check ' ?
		   	if ((*cmdline)[i + 1] == '\"')
				i++;
			else if ((*cmdline)[i + 1] == '\n')
			{
				st_cmd = get_st_cmd(NULL);//make func ?
				st_cmd->st_txt->data_size -= 2;
				ft_bzero(&st_cmd->st_txt->txt[st_cmd->st_txt->data_size], 2);
				ft_printf("end with '\\', READ_MODE");
				print_line();
				return (NULL);
			}
		}
		i++;
	}
	if ((*cmdline)[i] == 0)
	{
//		ft_printf("Unmatched \". READ_MODE PLZ");
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_DQ_STR)))
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
	{
		//ft_printf("Unmatched '. READ_MODE PLZ");
		//(*cmdline)[i] = '\n';// this don't change anything ??
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_SQ_STR)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_regular_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while ((*cmdline)[i] && !is_metachar((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, TK_WORD)))
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
		st_cmd = get_st_cmd(NULL);//make func ?
		st_cmd->st_txt->data_size -= 2;
		ft_bzero(&st_cmd->st_txt[st_cmd->st_txt->data_size], 2);
		return (NULL);
	}
	(*cmdline)++;
	if (!(token = create_token(*cmdline, 1, TK_MONOC)))
		ERROR_MEM;
	(*cmdline)++;
	return (token);
}

static t_token	*get_eat_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (is_white_spaces((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, TK_EAT)))
		ERROR_MEM;
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
	else if (is_white_spaces(**cmdline))
		return (get_eat_token(cmdline));
	else if ((token = get_op_chart_token(cmdline, op_chart)))
		return (token);
	else
		return (get_regular_token(cmdline));
}
