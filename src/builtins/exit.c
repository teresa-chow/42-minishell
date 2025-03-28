/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-25 19:44:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-25 19:44:11 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

void	exit_cmd(t_data *data, t_word_lst **word_lst, int *i)
{
	free_to_exit(data, word_lst);
	*i = 0;
}

void	check_exit_args(t_data *data, t_word_lst **word_lst, int *i)
{
	char	*tmp;
	int	check_many_args;
	int	check_syntax_error;

	check_many_args = 0;
	check_syntax_error = 0;
	tmp = NULL;
	if ((*word_lst)->word->next)
	{
		tmp = (*word_lst)->word->next->word;
		if ((*word_lst)->word->next->next)
			check_many_args = 1;
		data->exit_status = ft_atoi((*word_lst)->word->next->word);
	}
	while (tmp && *tmp)
	{
		if (!ft_isdigit(*tmp))
		{
			exit_error_syntax((*word_lst)->word->next->word, data);
			check_syntax_error = 1;
			break;
		}
		tmp++;
	}
	if (check_many_args && !check_syntax_error)
	{
		exit_error_many_args(data);
		return ;
	}
	exit_cmd(data, word_lst, i);
}
