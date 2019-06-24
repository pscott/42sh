/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libterm.h"
#include "errors.h"

/*
**	Prints the error_str, and err_file if provided. Exits with errno value.
*/

void	error_exit(int errno, const char *err_str, const char *err_file)
{
	if (err_file)
		ft_dprintf(2, "%s: %s\n", err_str, err_file);
	else
		ft_dprintf(2, "%s\n", err_str);
	exit(errno);
}
