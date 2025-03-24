/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:57:47 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/18 12:22:23 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	check_flag(char *word, int *has_flag)
{
	if (*word != '-' || ((*word == '-') && !*(word + 1)))
		return (0);
	else
		word = word + 1;
	while (*word)
	{
		if (*word != 'n')
			return (0);
		word++;
	}
	if (!*has_flag)
		*has_flag = 1;
	return (1);
}

t_word	*found_start(t_word *input, int *has_flag)
{
	while (input)
	{
		if (!check_flag(input->word, has_flag))
			return (input);
		input = input->next;
	}
	return (input);
}
void	echo(t_word *input)
{
	t_word	*start;
	int	has_flag;

	has_flag = 0;
	start = found_start(input->next, &has_flag);
	while (start)
	{
		ft_putstr_fd(start->word, STDOUT_FILENO);
		if (start->next)
			write (STDOUT_FILENO, " ", 1);
		start = start->next;
	}
	if (!has_flag)
		write (STDOUT_FILENO, "\n", 1);
}
