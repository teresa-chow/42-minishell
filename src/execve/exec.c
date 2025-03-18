/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:36:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 14:24:49 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"
/*
[ ]   /absolute/path/
[ ]  ../../relative/path/
[ ]  exec_name
[ ] ./user_exec
[ ] ./path/to/user_exec
[ ] $? 127 if cmd not found
*/

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

void	without_slash(t_data *data, t_word *word, char **tmp)
{
	char	**env_path;
	int	i;
	char	*tmp1;

	env_path = set_path(data);
	if (!env_path)
	{
		no_file_or_directory(word->word);
		return ;
	}
	i = -1;
	while (env_path[++i])
	{
		tmp1 = ft_strjoin(env_path[i], word->word );
		if (!tmp1)
		{
			error_allocation();
			return ;
		}
		if (!access(tmp1, F_OK) && !access(tmp1, X_OK))
		{
			*tmp = tmp1;
			return ;
		}
		free(tmp1);
	}
}

int	exec(t_data *data, t_word *word)
{
	char	**wrd_arr;
	char	**env_arr;
	char	*tmp;

	wrd_arr = creat_wrd_arr(word);
	env_arr = creat_env_arr(data->env);
	if (!wrd_arr || !env_arr)
		return (free_arrays(wrd_arr, env_arr, 1));
	tmp = NULL;
	if (!find_slash(word->word))
		without_slash(data, word, &tmp);
	if (tmp)
	{
		if (execve(tmp , wrd_arr, env_arr) < 0)
		{
			perror("execve failed");
			exit(127); // code to return ???
		}
	}
	free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
