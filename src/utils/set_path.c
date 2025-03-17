/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 09:41:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-17 09:41:12 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/error.h"

static char	*get_path(t_env_node *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	set_path(t_data *data)
{
	int	i;
	char	*tmp;

	data->env_path = ft_split(ft_strchr(get_path(data->env), '/'), ':');
	if (!data->env_path)
		return ;
	i = -1;	
	while (data->env_path[++i])
	{
		tmp = ft_strjoin(data->env_path[i], "/");
		if (!tmp)
		{
			free_strarray(data->env_path);
			data->env_path = NULL;
			error_allocation();
			return ;
		}
		free (data->env_path[i]);
		data->env_path[i] = tmp;
	}
}
