#include "tosh.h"

static void	create_op_chart_elem(t_operation *op, char *str
			, unsigned char size, t_token_type type)
{
	ft_strncpy(op->str, str, size + 1);
	op->size = size;
	op->type = type;
}

static void	fill_op_chart(t_operation *op_chart)
{
	create_op_chart_elem(&op_chart[0], ">>-", 3, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[1], "$((", 3, TK_42SH);
	create_op_chart_elem(&op_chart[2], ">>", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[3], "<<", 2, TK_HEREDOC);
	create_op_chart_elem(&op_chart[4], "&&", 2, TK_AND);
	create_op_chart_elem(&op_chart[5], "||", 2, TK_OR);
	create_op_chart_elem(&op_chart[6], ">&", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[7], "<&", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[8], "&>", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[9], "&<", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[10], ">|", 2, TK_42SH);
	create_op_chart_elem(&op_chart[11], "|&", 2, TK_42SH);
	create_op_chart_elem(&op_chart[12], "<>", 2, TK_42SH);
	create_op_chart_elem(&op_chart[13], "$(", 2, TK_42SH);
	create_op_chart_elem(&op_chart[14], "${", 2, TK_42SH);
	create_op_chart_elem(&op_chart[15], "))", 2, TK_42SH);
	create_op_chart_elem(&op_chart[16], "|", 1, TK_PIPE);
	create_op_chart_elem(&op_chart[17], "<", 1, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[18], ">", 1, TK_REDIRECTION);
	create_op_chart_elem(&op_chart[19], "&", 1, TK_AMP);
	create_op_chart_elem(&op_chart[20], ";", 1, TK_SEMI);
	op_chart[OP_CHART_SIZE - 1].size = 0;
}

t_operation	*get_op_chart(void)
{
	static t_operation	op_chart[OP_CHART_SIZE];

	fill_op_chart(op_chart);
	return (op_chart);
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
		printf("i: %d, str: {%s}, size: %d, type: %d\n",
				i,
				op_chart[i].str,
				op_chart[i].size,
				op_chart[i].type);
		i++;
	}
}
