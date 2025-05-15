/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:43:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/15 18:01:03 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/parse.h"
#include "../../include/errors.h"

static int	clean_env(t_env_node **env, char *word, t_data *data);
static int	update_env(t_env_node **env, t_env_node *tmp, t_data *data);

void	unset(t_data *data, t_word *word)
{
	while (word)
	{
		clean_env(&data->env, word->word, data);
		word = word->next;
	}
	data->exit_status = 0;
}

static int	update_env(t_env_node **env, t_env_node *tmp, t_data *data)
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
	if (!ft_strcmp(tmp->key, "HOME"))
	{
		data->no_home = true;
		data->env_home_var = NULL;
	}
	free(tmp->key);
	free(tmp->val);
	free(tmp);
	return (0);
}

static int	clean_env(t_env_node **env, char *word, t_data *data)
{
	t_env_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, word))
			return (update_env(env, tmp, data));
		tmp = tmp->next;
	}
	return (0);
}
