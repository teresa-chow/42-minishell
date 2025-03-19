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
int	cmd_exist_in_path(t_data *data, t_word *word, char **tmp)
{
	char	**env_path;
	char	*tmp1;
	int	i;

	env_path = set_path(data);
	if (!env_path)
		return (no_file_or_directory(word->word));
	i = -1;
	while (env_path[++i])
	{
		tmp1 = ft_strjoin(env_path[i], word->word );
		if (!tmp1)
			return (error_allocation());
		if (!access(tmp1, F_OK) && !access(tmp1, X_OK))
		{
			*tmp = tmp1;
			return (0);
		}
		free(tmp1);
	}
	return (command_not_found(word->word));
}
int	is_valid_path(t_word *word, char **tmp)
{
	DIR	*dir;
	
	dir = NULL;
	if (!access(word->word, F_OK))
	{
		dir = opendir(word->word);
		if (dir)
		{
			print_fd(2, "minishell: %s: Is a directory\n", word->word);
			// update error variable after print message
			// if (closedir(dir) < 0)
				// printf("ola\n");
		}
		else if (!access(word->word, X_OK))
			*tmp = word->word;
		else
		{
			//TODO: see how to handle with this
			print_fd(2, "minishell: %s: ", word->word);
			perror(NULL);
			// print_fd(2, "minishell: %s: %s", word->word, strerror(errno));
		}
	}
	else
		no_file_or_directory(word->word);
	return (0);
}

void	execute(char *tmp, char **wrd_arr, char **env_arr)
{
	pid_t	pid;

	pid = fork();
	// if (pid < 0)
	if (pid == 0)
	{
		if (execve(tmp , wrd_arr, env_arr) < 0)
		{
			perror("minishell");
			//exit ------>> with our exit
		}
	}
	else
		wait(NULL);
}
/* TODO:Check env with "." ". ./"  "//" , etc.....*/
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
		cmd_exist_in_path(data, word, &tmp); // this return an error code
	else
		is_valid_path(word, &tmp);
	if (tmp)
	{
		execute(tmp, wrd_arr, env_arr);
		free(tmp);
	}
	free_arrays(wrd_arr, env_arr, 0);
	return (0);
}
