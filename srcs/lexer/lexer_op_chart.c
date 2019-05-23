#include "42sh.h"
#include "lexer.h"

static void	create_op_chart_elem(t_operation *op, char *str
			, unsigned char size, t_token_type type)
{
	ft_strncpy(op->str, str, size + 1);
	op->size = size;
	op->type = type;
}

static void	fill_op_chart(t_operation *op_chart)
{
	create_op_chart_elem(&op_chart[0], ">>-", 3, tk_redirection);
	create_op_chart_elem(&op_chart[1], "$((", 3, tk_arith_exp);
	create_op_chart_elem(&op_chart[2], ">>", 2, tk_redirection);
	create_op_chart_elem(&op_chart[3], "<<", 2, tk_heredoc);
	create_op_chart_elem(&op_chart[4], "&&", 2, tk_and);
	create_op_chart_elem(&op_chart[5], "||", 2, tk_or);
	create_op_chart_elem(&op_chart[6], ">&", 2, tk_redirection);
	create_op_chart_elem(&op_chart[7], "<&", 2, tk_redirection);
	create_op_chart_elem(&op_chart[8], "&>", 2, tk_redirection);
	create_op_chart_elem(&op_chart[9], "&<", 2, tk_redirection);
	create_op_chart_elem(&op_chart[10], ">|", 2, tk_42sh);
	create_op_chart_elem(&op_chart[11], "|&", 2, tk_42sh);
	create_op_chart_elem(&op_chart[12], "<>", 2, tk_42sh);
	create_op_chart_elem(&op_chart[13], "$(", 2, tk_42sh);
	create_op_chart_elem(&op_chart[14], "${", 2, tk_42sh);
	create_op_chart_elem(&op_chart[15], "))", 2, tk_42sh);
	create_op_chart_elem(&op_chart[16], "|", 1, tk_pipe);
	create_op_chart_elem(&op_chart[17], "<", 1, tk_redirection);
	create_op_chart_elem(&op_chart[18], ">", 1, tk_redirection);
	create_op_chart_elem(&op_chart[19], "&", 1, tk_amp);
	create_op_chart_elem(&op_chart[20], ";", 1, tk_semi);
	op_chart[OP_CHART_SIZE - 1].size = 0;
}

t_operation	*get_op_chart(void)
{
	static t_operation	op_chart[OP_CHART_SIZE];

	fill_op_chart(op_chart);
	return (op_chart);
}

t_token		*get_arith_exp_token(char **cmdline)
{
	unsigned int	braces_count;
	int				i;
	t_token			*token;

	braces_count = 0;
	i = -1;
	ft_printf("cmdline: {%s}\n", *cmdline);
	while((*cmdline)[++i])
	{
		ft_printf("on %c\n", (*cmdline)[i]);
		if (!ft_strncmp("$((", &(*cmdline)[i], 3))
		{
			braces_count++;
			i += 3;
		}
		if (!ft_strncmp("))", &(*cmdline)[i], 2))
		{
			braces_count--;
			i += 2;
		}
	}
	ft_printf("braces: %d\ni: %d\n", braces_count, i);
	if (braces_count == 0)
		token = create_token(*cmdline, i, tk_arith_exp);
	else
	{
		ft_printf("ERROR (braces+count=%d)\n", braces_count);
		token = NULL;
	}
	print_token(token);
	return (NULL);
}

t_token		*get_op_chart_token(char **cmdline, t_operation *op_chart)
{
	int		i;
	t_token	*token;

	i = -1;
	while (op_chart[++i].size > 0)
	{
		if (!ft_strncmp(*cmdline, op_chart[i].str, op_chart[i].size))
		{
			if (op_chart[i].type == tk_arith_exp)
			{
				ft_printf("IS AN ARITH EXP\n");
				token = get_arith_exp_token(cmdline);
				ft_printf("IS AN ARITH EXP END\n");
				return (token);
			}
			if (!(token = create_token(*cmdline, op_chart[i].size,
							op_chart[i].type)))
				return (NULL);
			*cmdline = *cmdline + op_chart[i].size;
			return (token);
		}
	}
	return (NULL);
}

void		print_op_table(t_operation *op_chart)//for debug
{
	int		i;

	i = 0;
	while (op_chart[i].size != 0)
	{
		ft_dprintf(2, "i: %d, str: {%s}, size: %d, type: %d\n",
				i,
				op_chart[i].str,
				op_chart[i].size,
				op_chart[i].type);
		i++;
	}
}
