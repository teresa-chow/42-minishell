/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-28 08:46:10 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-28 08:46:10 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void    set_signals(t_data *data)
{
	signal (SIGINT, handle_signal);
	signal (SIGQUIT, SIG_IGN);
	if (global)
		data->exit_status = global;
}

void handle_signal(int i)
{
	write (1, "\n", 1);
	if (i == SIGINT)
		global = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
