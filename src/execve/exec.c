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

static char	*usr_exec(char *inpt)
{
	char	*c;
	char	*c1;

	c = ft_strchr(inpt, '.');
	c1 = c + 1;
	if (c && c1 && *c1 == '/')
		return (ft_strchr(inpt, '/') + 1);
	return (NULL);
}
void	exec(t_env_node *env, t_word *word)
{
	char	**wrd_arr;
	char	*path;
	char	**env_arr;

	wrd_arr = creat_wrd_arr(word);
	env_arr = creat_env_arr(env);
	if (!wrd_arr || !env_arr)
	{
		free_arrays(wrd_arr,env_arr, 1);
		return ;
	}
	if (usr_exec(word->word))
	{
		path = ft_strjoin(getcwd(NULL, 0), usr_exec(word->word));
		(void)path;
		// if (access(), F_OK) == -1)
		// 	perror("error");
		// else
		// 	execve("/home/carlaugu/42_commoncore/42-minishell/minishell", wrd_arr, env_arr);

	}
	free_arrays(wrd_arr, env_arr, 0);
}
