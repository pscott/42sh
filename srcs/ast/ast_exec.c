#include "lexer.h"
#include "cmd_parsing.h"
#include "execution.h"

static int		should_stop(int status, t_vars *vars)
{
	if (exit_status(status) == 254)
		return (256);
	else if (WIFSIGNALED(status))
	{
		vars->interrupted = WTERMSIG(status) == SIGINT ? 1 : 0;
		return (130);
	}
	return (0);
}

static int		ast_semi(t_ast *root, t_vars *vars, int fg)
{
	int ret;
	int	tmp;

	ret = exec_ast(root->left, vars, fg);
	if ((tmp = should_stop(ret, vars)))
		return (tmp);
	vars->cmd_value = exit_status(ret);
	return (exec_ast(root->right, vars, fg));
}

static int		ast_and(t_ast *root, t_vars *vars, int fg)
{
	int	ret;
	int tmp;

	ret = exec_ast(root->left, vars, fg);
	if ((tmp = should_stop(ret, vars)))
		return (tmp);
	return (exit_status(ret) ? ret : exec_ast(root->right, vars, fg));
}

static int		ast_or(t_ast *root, t_vars *vars, int fg)
{
	int	ret;
	int tmp;

	ret = exec_ast(root->left, vars, fg);
	if ((tmp = should_stop(ret, vars)))
		return (tmp);
	return (exit_status(ret) ? exec_ast(root->right, vars, fg) : ret);
}

int				exec_ast(t_ast *root, t_vars *vars, int fg)
{
	if (!root)
		return (0);
	if (vars->interrupted)
		return (130);
	if (root->token->type == tk_semi)
		return (ast_semi(root, vars, fg));
	else if (root->token->type == tk_amp)
		return (background_case(root, vars, fg));
	else if (root->token->type == tk_and)
		return (ast_and(root, vars, fg));
	else if (root->token->type == tk_or)
		return (ast_or(root, vars, fg));
	else
		return (parse_cmdline(root, vars, fg));
}
