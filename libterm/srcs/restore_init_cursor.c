/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_init_cursor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:29 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:29 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libterm.h"

void	restore_init_cursor(void)
{
	execute_str(VISIBLE);
	write(TERM_FD, FG_DFL, 3);
	execute_str(NO_HIGHLIGHT);
}
