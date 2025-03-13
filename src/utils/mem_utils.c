/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 12:06:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/parse.h"

void	free_strarray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_env_list(t_env_node *lst)
{
	t_env_node *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->var);
		lst = tmp;
  }
}

void	free_words(t_word **word)
{
	t_word	*tmp;

	while (*word != NULL)
	{
		free((*word)->word);
		tmp = *word;
		*word = (*word)->next;
		free(tmp);
	}
}

void	free_word_lst(t_word_lst **word_lst)
{
	t_word_lst	*tmp;

	while (*word_lst)
	{
		free_words(&(*word_lst)->word);
		tmp = *word_lst;
		*word_lst = (*word_lst)->next;
		free(tmp);
	}
}