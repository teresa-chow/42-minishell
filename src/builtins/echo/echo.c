/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:57:47 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 14:06:00 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/parse.h"

void	echo(t_world_list *input)
{
	int	flag;
	t_word_desc	*start;
	
	(void)flag;
	flag = input->word->next->flags;
	if (flag == 2)
		start = input->word->next->next;
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
