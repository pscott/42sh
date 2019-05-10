/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tgoto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:54:40 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		err_tgoto(char *cap)
{
	term_putstr_endline("error: failed to use tgoto with \"", 2);
	term_putstr_endline(cap ? cap : "(null)", 2);
	term_putstr_endline("\" cap.\n", 2);
	return (0);
}
