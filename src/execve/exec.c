/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:36:09 by carlaugu          #+#    #+#             */
/*   Updated: 2025/03/20 17:10:13 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	execute(char *input, t_data *data)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		return ;
	}
	else if (pid == 0)
		execve(input , data->wrd_arr, data->env_arr);
	else
		waitpid(pid, &status, 0);
	if (!status)
		data->exit_status = 0;
	else
		data->exit_status = WIFEXITED(status); 
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
int	cmd_exist_in_path(t_data *data, t_word *word, char **tmp, char **env_path)
{
	int	check;
	int	i;
	
	i = -1;
	while (env_path[++i])
	{
		*tmp = ft_strjoin(env_path[i], word->word );
		if (!*tmp)
			return (error_allocation(data));
		check = is_valid(*tmp, word, data);
		if (check == 1)
			return (1);
		else if (check < 0)
			return (0);
		free(*tmp);
		*tmp = NULL;
	}
	return (command_not_found(word->word, data));
}
void	is_in_env_path(t_data *data, t_word *word)
{
	char	*tmp;
	char	**env_path;
	
	tmp = NULL;
	env_path = set_path(data);
	if (!env_path)
	{
		free_arrays(data, 1);
		no_file_or_directory(word->word, data);
		return ;
	}
	if (cmd_exist_in_path(data, word, &tmp, env_path) == 1)
		execute(tmp, data);
	free_strarray(env_path);
	if (tmp)
		free(tmp);
}


void	exec(t_data *data, t_word *word)
{
	int	check;

	data->wrd_arr = creat_wrd_arr(word);
	data->env_arr = creat_env_arr(data->env);
	if (!data->wrd_arr || !data->env_arr)
	{
		free_arrays(data, 1);
		return ;	
	}
	if (!find_slash(word->word))
		is_in_env_path(data, word);
	else
	{
		check = is_valid(word->word, word, data);
		if (check == 1)
			execute(word->word, data);
		else if (!check)
			no_file_or_directory(word->word, data);
	}
	free_arrays(data, 0);
}
