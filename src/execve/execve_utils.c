/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:43:59 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 16:57:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execve.h"
#include "../../include/errors.h"

int	find_slash(char *word)
{
	while (*word)
	{
		if (*word == '/')
			return (1);
		word++;
	}
	return (0);
}

int	free_arrays(t_exec_data *inf, t_data *data, int i)
{
	free_strarray(inf->wrd_arr);
	free_strarray(inf->env_arr);
	if (inf->path_splited)
	{
		free_strarray(inf->path_splited);
		inf->path_splited = NULL;
	}
	inf->wrd_arr = NULL;
	inf->env_arr = NULL;
	if (i)
		return (error_allocation(data));
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
	int		i;
	char	**arr;

	arr = ft_calloc ((count_words(NULL, word) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
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
	int		i;
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
		if (arr[i] != tmp)
			free(arr[i]);
		arr[i] = tmp;
		env = env->next;
	}
	return (arr);
}
