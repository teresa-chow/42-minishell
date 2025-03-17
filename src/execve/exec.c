/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:36:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/12 14:20:49 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/error.h"
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
//WIFEXITED(status) --------------------------------------------------------
int	handle_sys_exec(char **wrd_arr, char **env_arr, t_data *data)
{
	int	i;
	char	*tmp;
	char	**env_path;
	pid_t	pid;

	env_path = set_path(data);
	if (!env_path)
	return (command_not_found(data->word_lst.word->word));	
	i = -1;
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], data->word_lst.word->word);
		if (!tmp)
		{
			error_allocation();
			break;
		}
		if (access(tmp, F_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(tmp, wrd_arr, env_arr);
			else
			{
				wait (NULL);
				break;
			}
		}
	}
	printf("%d\n", errno);
	free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
int	exec(t_data *data)
{
	char	**wrd_arr;
	char	**env_arr;

	wrd_arr = creat_wrd_arr(data->word_lst.word);
	env_arr = creat_env_arr(data->env);
	if (!wrd_arr || !env_arr)
		return (free_arrays(wrd_arr, env_arr, 1));
	if (!find_slash(data->word_lst.word->word))
	{
		handle_sys_exec(wrd_arr, env_arr, data);

	}
	else
		free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
