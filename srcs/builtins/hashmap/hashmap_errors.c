/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:06 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:10 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

int	print_hash_invalid_option(char c)
{
	ft_dprintf(2, "-%c: invalid option\n", c);
	ft_dprintf(STDERR_FILENO,
		"hash usage [-lr] [-p pathname] [-d] [name ...]\n");
	return (0);
}
