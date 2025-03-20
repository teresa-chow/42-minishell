/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:36:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/19 14:28:29 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	execute(char *input, t_data *data)
{
	pid_t	pid;

	pid = fork();
	// if (pid < 0)
	if (pid == 0)
	{
		if (execve(input , data->wrd_arr, data->env_arr) < 0)
		{
			perror("minishell");
			exit(1); //------>> with our exit and check error code to return
		}
	}
	else
		wait(NULL);
}
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
int	is_valid(char *input, t_word *word, t_data *data)
{
	(void)data;

	struct stat info;

	ft_bzero(&info, sizeof(info));
	if (!access(input, F_OK))
	{
		stat(input, &info);
		if (S_ISDIR(info.st_mode))
			return (is_a_directory(word->word, data));
		else if (!access(input, X_OK))
			return (1);
		else
			return(access_error(word->word, data));
	}
	return (0);
}
int	cmd_exist_in_path(t_data *data, t_word *word, char **tmp)
{
	char	**env_path;
	char	*tmp1;
	int	check;
	int	i;
	
	env_path = set_path(data);
	if (!env_path)
		return (no_file_or_directory(word->word, data));
	i = -1;
	while (env_path[++i])
	{
		tmp1 = ft_strjoin(env_path[i], word->word );
		if (!tmp1)
			return (error_allocation(data));
		check = is_valid(tmp1, word, data);
		if (check == 1)
		{
			*tmp = tmp1;
			return (1);
		}
		else if (check < 0)
			return (0);
		free(tmp1);
	}
	return (command_not_found(word->word, data));
}
/* TODO:Check env with "." ". ./"  "//" , etc.....*/
int	exec(t_data *data, t_word *word)
{
	char	*tmp;
	int	check;

	tmp =NULL;
	data->wrd_arr = creat_wrd_arr(word);
	data->env_arr = creat_env_arr(data->env);
	if (!data->wrd_arr || !data->env_arr)
		return (free_arrays(data, 1));
	if (!find_slash(word->word))
	{
		if (cmd_exist_in_path(data, word, &tmp) == 1)
			execute(tmp, data);
		if (tmp)
			free(tmp);
	}
	else
	{
		check = is_valid(word->word, word, data);
		if (check == 1)
			execute(word->word, data);
		else if (!check)
			no_file_or_directory(word->word, data);
	}
	free_arrays(data, 0);
	return (0);
}
