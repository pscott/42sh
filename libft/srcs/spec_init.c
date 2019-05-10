/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:24 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_specs(t_arg *specs)
{
	specs->type = 0;
	specs->width = 0;
	specs->width_len = 0;
	specs->precision = 0;
	specs->precision_len = 0;
	specs->fill = 0;
	specs->fill_len = 0;
	specs->left = 0;
	specs->plus = 0;
	specs->hash = 0;
	specs->l = 0;
	specs->dbl = 0;
	specs->h = 0;
	specs->mall_len = INIT_LEN;
	specs->string = NULL;
	specs->origin = NULL;
	specs->data_len = 0;
	specs->extra = 0;
}

void	reset_specs(t_arg *specs)
{
	specs->type = 0;
	specs->width = 0;
	specs->width_len = 0;
	specs->precision = 0;
	specs->precision_len = 0;
	specs->fill = 0;
	specs->fill_len = 0;
	specs->left = 0;
	specs->plus = 0;
	specs->hash = 0;
	specs->l = 0;
	specs->dbl = 0;
	specs->h = 0;
	specs->data_len = 0;
	specs->extra = 0;
}

void	realloc_if_necessary(t_arg *specs, int len)
{
	if (specs->string - specs->origin + len >= specs->mall_len - 1)
		malloc_string(specs, len);
}

void	malloc_string(t_arg *specs, int len)
{
	char	*tmp;
	int		to_cpy;

	while (specs->string - specs->origin + len >= specs->mall_len - 1)
		specs->mall_len *= 2;
	if (!(specs->string))
	{
		if (!(specs->string = ft_strnew(specs->mall_len)))
			return ;
		specs->origin = specs->string;
	}
	else
	{
		if (!(tmp = ft_strnew(specs->mall_len)))
			return ;
		to_cpy = specs->string - specs->origin + 1;
		ft_memcpy(tmp, specs->origin, to_cpy);
		free(specs->origin);
		specs->string = tmp;
		specs->origin = tmp;
		specs->string += to_cpy - 1;
	}
}

t_arg	*create_specs(t_arg *specs)
{
	if (!(specs = (t_arg *)malloc(sizeof(t_arg))))
	{
		ft_putendl("MALLOC");
		return (NULL);
	}
	init_specs(specs);
	malloc_string(specs, 0);
	return (specs);
}
