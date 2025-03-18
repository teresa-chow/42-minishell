/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:43:59 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 14:24:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

char	*get_path(t_env_node *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

int	free_arrays(char **wrd_arr, char **env_arr, int i)
{
	free_strarray(wrd_arr);
	wrd_arr = NULL;
	free_strarray(env_arr);
	env_arr = NULL;
	if (i)
		return(error_allocation());
	return (0);
}

static int	count_words(t_env_node *env, t_word *word)
{
	int	count;

	count = 0;
	if (env)
	{
		while (env)
		{
			count++;
			env = env->next;
		}
	}
	else
	{
		while (word)
		{
			count++;
			word = word->next;
		}
	}
	return (count);
}

char	**creat_wrd_arr(t_word *word)
{
	int	i;
	char	**arr;

	arr = ft_calloc ((count_words(NULL, word) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	word = word;
	i = -1;
	while (word)
	{
		arr[++i] = ft_strdup(word->word);
		if (!arr[i])
			return (NULL);
		word = word->next; 
	}
	return (arr);
}

char	**creat_env_arr(t_env_node *env)
{
	int	i;
	char	**arr;
	char	*tmp;

	arr = ft_calloc ((count_words(env, NULL) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (env)
	{
		arr[++i] = ft_strjoin(env->key, "=");
		if (!arr[i])
			return (NULL);
		tmp = ft_strjoin(arr[i], env->val);
		if (!tmp)
			return (NULL);
		free(arr[i]);
		arr[i] = tmp;
		env = env->next; 
	}
	return (arr);
}
