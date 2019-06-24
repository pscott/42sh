/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:17 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:21 by penzo            ###   ########.fr       */
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
