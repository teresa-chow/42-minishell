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

void	check_cmd(char **env_path, t_data *data, char **tmp)
{
	int	i;
	char	*tmp1;

	tmp1 = NULL;
	i = -1;
	while (env_path[++i])
	{
		tmp1 = ft_strjoin(env_path[i], data->word_lst.word->word);
		if (!tmp1)
		{
			error_allocation();
			return ;
		}
		if (access(tmp1, F_OK) == 0 && access(tmp1, X_OK) == 0)
		{
			*tmp = tmp1;
			return ;
		}
		else
			free(tmp1);
	}
}
//WIFEXITED(status) --------------------------------------------------------
int	handle_sys_exec(char **wrd_arr, char **env_arr, t_data *data)
{
	char	*tmp;
	pid_t	pid;
	char	**env_path;

	env_path = set_path(data);
	if (!env_path)
		return (command_not_found(data->word_lst.word->word));
	tmp = NULL;
	check_cmd(env_path, data, &tmp);
	if (tmp)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(tmp, wrd_arr, env_arr);
			perror("exeve failed!");
			exit(ERR_X);
		}
		else
		{
			wait(NULL);
			free(tmp);
		}
	}
	else
		command_not_found(data->word_lst.word->word);
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
