/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/02 14:59:04 by tchow-so         ###   ########.fr       */
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

void	free_prompt(t_prompt *prompt)
{
	if (prompt->prog)
		free(prompt->prog);
	if (prompt->usr)
		free(prompt->usr);
	if (prompt->cwd)
		free(prompt->cwd);
}

int	free_env_list(t_data *data, int i, t_env_node **lst)
{
	t_env_node *tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->val);
		free((*lst));
		(*lst) = tmp;
  	}
	*lst = NULL;
	if (i)
		return (error_allocation(data));
	return (0);
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
void	free_to_exit(t_data *data, t_word_lst **word_lst)
{
	free_env_list(data, 0, &data->env);
	free_word_lst(word_lst);
}
