//#include "42sh.h"
#include "expand.h"
#include "exp_arith.h"

//9223372036854775807
static	char	*lltoa(long long nb)
{
	char	*str;
	char	i;
	char	buf;

	if (!(str = ft_strnew(20)))
		ERROR_MEM;
	i = 19;
	while (i)
	{
		buf = (nb % 10) + 48;
		str[i] = buf;
		nb = nb / 10;
		i--;
	}
	return (str);
}

static	size_t	get_ll_len(long long nb)
{
	size_t	len;

	len = 0;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char	*susbitute_arith_exp(char *old_str, size_t start_index
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
	char_nb = lltoa(result);//already protected in lltoa cause we exit
	ft_strncpy(&new_str[start_index], char_nb, ft_strlen(char_nb));
	ft_strncpy(&new_str[start_index + ft_strlen(char_nb)]
			,&old_str[end_index + 1], ft_strlen(&old_str[end_index + 1]));
	//TODO HERE HERE HERE HERE !!!!!!!!!!!!1
	return (new_str);
}

//this function will not receive escaped 
char	*get_lowest_arith_exp(char *str, t_vars *vars)
{
	size_t	i;
	size_t	start_mark;
	size_t	end_mark;
	long long	arith_result;

	i = 0;
	arith_result = 0;
	while (str[i])
	{
		if (!(ft_strncmp("$((", str + i, 3)))
			start_mark = i + 3;
		if (!(ft_strncmp("))", str + i, 2)))
		{
			end_mark = i;
			ft_printf("send: |%s|\n", ft_strndup(&str[start_mark], end_mark - start_mark));
			if (expansion_arith(ft_strndup(&str[start_mark], end_mark - start_mark), &vars->shell_vars, &arith_result))
			{
				ft_printf("SDFSDF\n");
				return (NULL);
			}
			ft_printf("result = %lld\n", arith_result);
			//REPLACE HERE
			susbitute_arith_exp(str, start_mark, end_mark, arith_result)
		}
		i++;
	}
	return (NULL);//tmp
}

//the $(( at index is terminated
t_token	*replace_all_arith_exp(char **str, size_t *index, t_vars *vars)
{
	char	*new_str;
	size_t	i;

	i = *index;
	while (get_lowest_arith_exp(**str, vars))
		;
}
