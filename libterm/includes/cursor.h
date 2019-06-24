/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:29 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:29 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

# include "libft.h"
# include <unistd.h>

# define BEGIN_LINE "cr"
# define INVISIBLE "vi"
# define VISIBLE "ve"
# define CLEAR "cl"
# define CLEAR_BELOW "cd"
# define MOVE_DOWN "do"
# define ERASE_ENDLINE "ce"
# define HIGHLIGHT "so"
# define NO_HIGHLIGHT "se"
# define SCROLL_DOWN "sf"
# define MOVE_UP "up"
# define MOVE_RIGHT "nd"
# define MOVE_LEFT "le"
# define NUM_CAPS 13

typedef struct	s_pos {
	int	row;
	int	col;
}				t_pos;

#endif
