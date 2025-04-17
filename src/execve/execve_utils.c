/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:43:59 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 13:29:20 by carlaugu         ###   ########.fr       */
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
			if (word->redir != NONE)
				word = word->next;
			else
				count++;
			word = word->next;
		}
	}
	return (count);
}

char	**create_wrd_arr(t_word *word)
{
	int		i;
	char	**arr;

	arr = ft_calloc ((count_words(NULL, word) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (word)
	{
		if (word->redir == NONE)
		{
			arr[++i] = ft_strdup(word->word);
			if (!arr[i])
			return (NULL);
		}
		else
			word = word->next;
		word = word->next;
	}
	return (arr);
}

char	**create_env_arr(t_env_node *env)
{
	int		i;
	char	**arr;

	arr = ft_calloc ((count_words(env, NULL) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (env)
	{
		if (env->val)
			arr[++i] = join_three(env->key, "=", env->val);
		else
			arr[++i] = join_three(env->key, NULL, NULL);
		if (!arr[i])
			return (NULL);
		env = env->next;
	}
	return (arr);
}
