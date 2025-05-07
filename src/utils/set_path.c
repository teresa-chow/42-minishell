/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:41:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/07 11:29:19 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"

static void	get_path(char **tmp, t_data *data, int *i);

char	**set_path(t_data *data, int *i)
{
	int		j;
	char	*tmp;
	char	**arr;

	tmp = NULL;
	arr = NULL;
	get_path(&tmp, data, i);
	if (ft_strchr(tmp, '/'))
		arr = ft_split(ft_strchr(tmp, '/'), ':');
	else
		arr = ft_split(tmp, ' ');
	if (!arr)
		return (NULL);
	j = -1;
	while (arr[++j])
	{
		tmp = ft_strjoin(arr[j], "/");
		if (!tmp)
		{
			free_strarray(arr);
			return (NULL);
		}
		free (arr[j]);
		arr[j] = tmp;
	}
	return (arr);
}

static void	get_path(char **tmp, t_data *data, int *i)
{
	t_env_node	*path_node;

	path_node = ft_getenv(data->env, "PATH");
	if (path_node)
		*tmp = path_node->val;
	else
		*i = -1;
}
