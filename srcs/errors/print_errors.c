/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
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

int		print_errors(int errno, const char *err_str, const char *err_file)
{
	if (err_file)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", err_str, err_file);
	else
		ft_dprintf(STDERR_FILENO, "%s\n", err_str);
	return (errno);
}
