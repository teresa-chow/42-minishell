/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:41:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 17:45:11 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"

char	**set_path(t_data *data)
{
	int		i;
	char	*tmp;
	char	**arr;

	arr = ft_split(ft_strchr(get_var(data->env, "PATH")->val, '/'), ':');
	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		tmp = ft_strjoin(arr[i], "/");
		if (!tmp)
		{
			free_strarray(arr);
			return (NULL);
		}
		free (arr[i]);
		arr[i] = tmp;
	}
	return (arr);
}
