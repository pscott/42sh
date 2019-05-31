//#include "42sh.h"
#include "expand.h"
#include "exp_arith.h"

static	size_t	get_ll_len(long long nb)
{
	size_t	len;

	len = (nb < 0) ? 1 : 0;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char	*lltoa(long long nb)
{
	char		*str;
	int			len;

	len = get_ll_len(nb);
	if (!(str = ft_strnew(len)))
		ERROR_MEM;
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		str[len-- - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}

/*
static char	*substitute_arith_exp(char *old_str, size_t start_index
			, size_t end_index, long long result)
{
	char	*new_str;
	char	*char_nb;
	size_t	new_len;
	size_t	i;


	i = 0;
	new_len = ft_strlen(old_str)
		+ get_ll_len(result)
		- ((end_index + 1) - start_index);
	if (!(new_str = ft_strnew(new_len)))
		ERROR_MEM;
	ft_strncpy(new_str, old_str, start_index);
	char_nb = lltoa(result);
	ft_strncpy(&new_str[start_index], char_nb, ft_strlen(char_nb));
	ft_strncpy(&new_str[start_index + ft_strlen(char_nb)]
			,&old_str[end_index + 2], ft_strlen(&old_str[end_index + 1]));
	ft_strdel(&char_nb);
	return (new_str);
}
*/

//OLD
//this function will not receive escaped str
/*
t_bool	get_lowest_arith_exp(char **str, t_vars *vars)
{
	size_t	i;
	size_t	start_mark;
	size_t	end_mark;
	long long	arith_result;
	char	*new_str;

	i = 0;
	arith_result = 0;
	while ((*str)[i])
	{
		if (!(ft_strncmp("$((", *str + i, 3)))
			start_mark = i + 3;
		if (!(ft_strncmp("))", *str + i, 2)))
		{
			end_mark = i;
			new_str = ft_strndup(&(*str)[start_mark], end_mark - start_mark);
			if (expansion_arith(new_str, &vars->shell_vars, &arith_result))
			{
				ft_strdel(&new_str);
				return (0);
			}
			ft_strdel(&new_str);
			new_str = substitute_arith_exp(*str, start_mark - 3, end_mark, arith_result);
			ft_strdel(str);
			*str = new_str;
			return (1);
		}
		i++;
	}
	return (0);//tmp
}
*/

//TODO rename expand_lowest
char	get_lowest_arith_exp(char **str, t_vars *vars)
{
	size_t	i;
	size_t	index[2];
	long long	arith_result;

	i = 0;
	arith_result = 0;
	while ((*str)[i])
	{
		if (!(ft_strncmp("$((", *str + i, 3)))
			index[0] = i;
		if (!(ft_strncmp("))", *str + i, 2)))
		{
			index[1] = i + 2;
			if (expansion_arith(*str, &vars->shell_vars, &arith_result))
				return (-1);
			substitute_slice(str, index, lltoa(arith_result));
			return (1);
		}
		i++;
	}
	return (0);
}

//FULL USELESS
//the $(( at index is terminated
//t_token	*replace_all_arith_exp(char **str, size_t *index, t_vars *vars)
/*
t_bool		replace_all_arith_exp(char **str, size_t *index, t_vars *vars)
{
	//char	*new_str;
	size_t	i;

	i = *index;
	while (get_lowest_arith_exp(str, vars))//TODO rework this
	{
		ft_printf("TOP: |%s|\n", *str);
	}
	return (1);//TMP
}
*/
