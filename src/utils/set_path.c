/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:41:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 11:23:56 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/errors.h"

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

char	**set_path(t_data *data)
{
	int	i;
	char	*tmp;
	char	**arr;

	arr = ft_split(ft_strchr(get_path(data->env), '/'), ':');
	if (!arr)
		return (NULL);
	i = -1;	
	while (arr[++i])
	{
		tmp = ft_strjoin(arr[i], "/");
		if (!tmp)
		{
			free_strarray(arr);
			arr = NULL;
			error_allocation(data);
			return (NULL);
		}
		free (arr[i]);
		arr[i] = tmp;
	}
	return (arr);
}
