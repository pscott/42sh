/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:18 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:21 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "ftsh.h"
# include <signal.h>
# include <sys/ioctl.h>

void	sigint_handler(int signo);
void	sigcont_handler(int signo);
void	sigwinch_handler(int signo);
void	sigtstp_handler(int signo);
void	sigquit_handler(int signo);
void	signals_setup(void);

#endif
