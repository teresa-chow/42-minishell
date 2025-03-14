/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:57:47 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/12 13:33:30 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"

/* TODO: check here if there is -n or -nnnn, etc*/
void	echo(t_word *input)
{
	int	flag;
	t_word	*start;

	flag = 0;
	if (input->next != NULL)
		flag = input->next->flags;
	if (flag == 2)
		start = input->next->next;
	else
		start = input->next;
	while (start)
	{
		ft_putstr_fd(start->word, 1);
		if (start->next)
			write (1, " ", 1);
		start = start->next;
	}
	if (flag != 2)
		write (1, "\n", 1);
}
