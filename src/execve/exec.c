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
int	handle_sys_exec(char **wrd_arr, char **env_arr, t_word *word)
{
	int	i;
	pid_t	pid;
	char	*env_path;
	char	**path;
	char	*box;
	char	*box1;

	(void)box1;
	pid = fork();
	env_path = get_path(env_arr);
	path = ft_split(ft_strchr(env_path, '=') + 1, ':');
	i = -1;
	while (path[++i])
	{
		box = ft_strjoin("/", word->word);
		box1 = path[i];
		path[i] = ft_strjoin(path[i], box);
		if (!access(path[i], F_OK) && !access(path[i], X_OK))
		{
			if (pid < 0)
			{
				perror("fork failed");
				///how to do here if fail??? return error code?
			}
			else if (pid == 0)
			{
				if (execve(path[i], wrd_arr, env_arr) < 0)
					perror("errorwe");
			}
			else
				wait(NULL);
		}
		// else
		// 	perror("error"); i have to see this
	}
	return (0);
}

int	exec(t_env_node *env, t_word *word)
{
	char	**wrd_arr;
	char	**env_arr;


	wrd_arr = creat_wrd_arr(word);
	env_arr = creat_env_arr(env);
	if (!wrd_arr || !env_arr)
		return (free_arrays(wrd_arr, env_arr, 1));
	if (!find_slash(word->word))
	{
		handle_sys_exec(wrd_arr, env_arr, word);
	}
	free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
