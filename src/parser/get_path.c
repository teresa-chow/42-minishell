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

#include "../../include/parse.h"

static int	ft_strcmp(const char *s1, const char *s2);

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
			return (env_var);
		i++;
	}
	return (env_var);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}