#include "ftsh.h"
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
	create_op_chart_elem(&op_chart[0], ">>-", 3, tk_redirection);//nop //tk_unsupported ??
	//create_op_chart_elem(&op_chart[1], "$((", 3, tk_arith_exp);//no need as i check it in get_token before get_op_chart_token
	create_op_chart_elem(&op_chart[1], ">>", 2, tk_redirection);
	create_op_chart_elem(&op_chart[2], "<<", 2, tk_heredoc);
	create_op_chart_elem(&op_chart[3], "&&", 2, tk_and);
	create_op_chart_elem(&op_chart[4], "||", 2, tk_or);
	create_op_chart_elem(&op_chart[5], ">&", 2, tk_redirection);
	create_op_chart_elem(&op_chart[6], "<&", 2, tk_redirection);
	create_op_chart_elem(&op_chart[7], "&>", 2, tk_redirection);//nop
	create_op_chart_elem(&op_chart[8], "&<", 2, tk_redirection);//nop
	create_op_chart_elem(&op_chart[9], ">|", 2, tk_unsupported);//nop
	create_op_chart_elem(&op_chart[10], "|&", 2, tk_unsupported);//nop
	create_op_chart_elem(&op_chart[11], "<>", 2, tk_unsupported);//nop
	create_op_chart_elem(&op_chart[12], "$(", 2, tk_42sh);//nop
	//create_op_chart_elem(&op_chart[14], "${", 2, tk_42sh);//need this
	//create_op_chart_elem(&op_chart[14], "${", 2, tk_word);//maybe don't tokenise it and just parse it in expand dollars ?
	//create_op_chart_elem(&op_chart[15], "))", 2, tk_42sh);//no need: cause a call get_arith_exp()
	create_op_chart_elem(&op_chart[13], ")", 1, tk_unsupported);//make tk_unsupported
	//create_op_chart_elem(&op_chart[14], "(", 1, tk_unsupported);//TODO make this token too
	create_op_chart_elem(&op_chart[14], "|", 1, tk_pipe);
	create_op_chart_elem(&op_chart[15], "<", 1, tk_redirection);
	create_op_chart_elem(&op_chart[16], ">", 1, tk_redirection);
	create_op_chart_elem(&op_chart[17], "&", 1, tk_amp);
	create_op_chart_elem(&op_chart[18], ";", 1, tk_semi);
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
			//if (op_chart[i].type == tk_arith_exp)//useless ?? 
			//{
			//	if (!(token = get_arith_exp_token(cmdline)))
			//	{
			//		ft_printf("get_arith didn't find the end \n");
			//		return (NULL);
			//	}
			//	return (token);
			//}
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
