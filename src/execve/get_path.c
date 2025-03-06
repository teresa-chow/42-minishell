/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:48:04 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/26 16:48:04 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execve.h"
#include "../../include/utils.h"

char	*get_path(char **envp)
{
	char	*env_var;
	char	**key;
	int		i;

	i = 0;
	env_var = envp[i];
	while (env_var != NULL)
	{
		env_var = envp[i];
		key = ft_split(env_var, '=');
		if (ft_strcmp(key[0], "PATH") == 0)
		{
			free_strarray(key);
			return (env_var);
		}
		free_strarray(key);
		i++;
	}
	return (env_var);
}