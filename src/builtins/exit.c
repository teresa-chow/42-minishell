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

int	exit_cmd(t_data *data, t_word_lst **word_lst)
{
	if ((*word_lst)->word->next)
		data->exit_status = ft_atoi((*word_lst)->word->next->word);
	free_to_exit(data, word_lst);
	return (data->exit_status);
}