/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-26 22:19:43 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-26 22:19:43 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	cmd_and_args_check(t_data *data, t_word_lst **word_lst)
{
	t_word_lst	*last_cmd;
	t_word_lst	*tmp;

	tmp = *word_lst;
	last_cmd = tmp;
	while (tmp)
	{
		if (ft_strcmp(tmp->word->word, "echo") == 0)
			return (1);
		else if (ft_strcmp(tmp->word->word, "cd") == 0)
			return (1);
		else if (ft_strcmp(tmp->word->word, "pwd") == 0)
			return (1);
		else if (ft_strcmp(tmp->word->word ,"export") == 0)
		{
			if (tmp->word->next)
			{
				check_export_args(tmp->word, data);
				check_if_has_args(last_cmd, &tmp, word_lst);
				// if we have export with arguments and the argument
				//is not valid, here i make free the argument and if in the end
				//we have only "expo" whithout arguments i free node of export
			}
		}



		
		// else if (ft_strcmp((*word_lst)->word->word,"unset") == 0)
		
		// else if (ft_strcmp((*word_lst)->word->word,"env") == 0)
		
		// else
		// 	exec(data, word_lst->word);
		last_cmd = tmp;
		if (tmp)
			tmp= tmp->next;
	}
	return (0);
}