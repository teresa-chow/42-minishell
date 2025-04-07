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

void	check_syntax(t_word *word, t_data *data, int *many_args, int *syntax)
{
	char	*tmp;

	tmp = NULL;
	if (word->next)
	{
		tmp = word->next->word;
		if (word->next->next)
			*many_args = 1;
		data->exit_status = ft_atoi(word->next->word);
	}
	while (tmp && *tmp)
	{
		if (!ft_isdigit(*tmp))
		{
			exit_error_syntax(word->next->word, data);
			*syntax = 1;
			break ;
		}
		tmp++;
	}
}

void	check_exit_args(t_data *data, t_word_lst **word_lst, int *i)
{
	int		many_args;
	int		syntax_error;

	many_args = 0;
	syntax_error = 0;
	check_syntax((*word_lst)->word, data, &many_args, &syntax_error);
	if (many_args && !syntax_error)
	{
		exit_error_many_args(data);
		return ;
	}
	exit_cmd(data, word_lst, i);
}
