/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:36:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/18 11:27:18 by carlaugu         ###   ########.fr       */
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

int	exec(t_data *data)
{
	char	**wrd_arr;
	char	**env_arr;

	wrd_arr = creat_wrd_arr(data->word_lst.word);
	env_arr = creat_env_arr(data->env);
	if (!wrd_arr || !env_arr)
		return (free_arrays(wrd_arr, env_arr, 1));
	if (!find_slash(data->word_lst.word->word))
		without_slash(data);
	else
		free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
