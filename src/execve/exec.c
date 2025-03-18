/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:36:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 12:24:02 by carlaugu         ###   ########.fr       */
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
//WIFEXITED(status)
int	handle_sys_exec(char **wrd_arr, char **env_arr, t_data *data)
{
	int	i;
	char	*tmp;

	(void)wrd_arr;
	(void)env_arr;
	(void)tmp;
	i = -1;
	set_path(data);
	if (!data->env_path)
		return (command_not_found(data->word_lst.word->word));	
	while (data->env_path[++i])
	{
		tmp = ft_strjoin(data->env_path[i], "/");
		// if (access())
	}
	// free_arrays(wrd_arr, env_arr, 0); ???????
	return (0);
}

// int	find_slash(char *word)
// {
// 	while (*word)
// 	{
// 		if (*word == '/')
// 			return (1);
// 		word++;
// 	}
// 	return (0);
// }
// void	without_slash(t_data *data)
// {
// 	char	**env_path;
// 	int	i;

// 	env_path = set_path(data);
// 	if (!env_path)
// 	{
// 		no_file_or_directory(data->word_lst.word->word);
// 		return ;
// 	}
// 	i = -1;
// 	while (env_path[++i])
// 	{
// 		tmp = ft_strjoin();	
// 	}
// }

int	exec(t_data *data, t_word *word)
{
	char	**wrd_arr;
	char	**env_arr;

	wrd_arr = creat_wrd_arr(word);
	env_arr = creat_env_arr(data->env);
	if (!wrd_arr || !env_arr)
		return (free_arrays(wrd_arr, env_arr, 1));
	// if (!find_slash(word->word))
	// 	without_slash(data);
	// else
	// 	free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
