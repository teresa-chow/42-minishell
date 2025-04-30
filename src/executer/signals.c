/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:46:10 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 18:44:28 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	set_signals(void)
{
	signal (SIGINT, handle_signal);
	signal (SIGQUIT, SIG_IGN);
}

void	handle_signal(int i)
{
	write (1, "\n", 1);
	if (i == SIGINT)
		global = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
