/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-14 21:43:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-14 21:43:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/parse.h"
#include "../../include/errors.h"

static int	update_env(t_env_node **env, t_env_node *tmp)
{
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	else
	{
		*env = tmp->next;
		if (*env)
			(*env)->prev = NULL;
	}
	free(tmp->key);
	free(tmp->val);
	free(tmp);
	return (0);
}

static int	clean_env(t_env_node **env, char *word)
{
	t_env_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, word))
			return(update_env(env, tmp));
		tmp = tmp->next;
	}
	return (0);
}

void	unset(t_data *data)
{
	t_word *word_lst;

	word_lst = data->word_lst.word->next;
	while (word_lst)
	{
		if (clean_env(&data->env, word_lst->word) == -1)
			return ;
		word_lst = word_lst->next;
	}
}