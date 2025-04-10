/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 17:55:27 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/parse.h"
#include "../../include/errors.h"

void	free_strarray(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_word_lst(t_word_lst **word_lst)
{
	t_word_lst	*tmp;

	while (*word_lst)
	{
		tmp = *word_lst;
		*word_lst = (*word_lst)->next;
		free(tmp);
	}
}

void	free_w_lst_words(t_word_lst **word_lst)
{
	t_word_lst	*tmp;

	while (*word_lst)
	{
		tmp = *word_lst;
		free_words(&tmp->word);
		*word_lst = (*word_lst)->next;
		free(tmp);
	}
}

void	free_prompt(t_prompt *prompt)
{
	if (prompt->prog)
		free(prompt->prog);
	if (prompt->usr)
		free(prompt->usr);
	if (prompt->cwd)
		free(prompt->cwd);
}
