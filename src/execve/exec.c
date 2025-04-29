/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:19:13 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/29 15:07:09 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

static int	set_exec_inf(t_exec_data *inf, t_data *data, t_word *word);
static int	cmd_in_env_path(t_exec_data *inf, t_data *data);
static void	execute(t_exec_data *inf);
static void	check_cmd(t_exec_data *inf, t_data *data);

int	exec_external(t_data *data, t_word *word)
{
	t_word	*tmp;
	t_exec_data	inf;

	tmp = word;
	while (tmp && tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!tmp)
		return (0);
	if (set_exec_inf(&inf, data, tmp) == -1)
		return (data->exit_status);
	if (!find_slash(inf.input))
	{
		if (cmd_in_env_path(&inf, data) == 1)
			check_cmd(&inf, data);
	}
	else
	{
		inf.tmp = inf.input;
		if (!access(inf.input, F_OK))
			check_cmd(&inf, data);
		else
			no_file_or_dir(inf.input, data, 0);
	}
	free_arrays(&inf, data, 0); //group
	free_env_list(data, 0, &data->env); //group
	free_ast(&data->ast_root); //group
	exit(data->exit_status);
}

static int	set_exec_inf(t_exec_data *inf, t_data *data, t_word *word)
{
	int	i;

	i = 0;
	ft_bzero(inf, sizeof(t_exec_data));
	inf->input = word->word;
	inf->wrd_arr = create_wrd_arr(word);
	inf->env_arr = create_env_arr(data->env);
	if (!inf->wrd_arr || !inf->env_arr)
		return (free_arrays(inf, data, 1));
	inf->path_splited = set_path(data, &i);
	if (!inf->path_splited && i != -1)
		return (free_arrays(inf, data, 1));
	else if (!inf->path_splited && i == -1)
	{
		if (!access(word->word, F_OK))
		{
			inf->tmp = inf->input;
			if (!access(word->word, X_OK))
				execute (inf);
			return (-1);
		}
	}
	return (0);
}

static int	cmd_in_env_path(t_exec_data *inf, t_data *data)
{
	int	i;

	if (!inf->path_splited)
	{
		no_file_or_dir(inf->input, data, 0);
		return (-1);
	}
	i = -1;
	while (inf->path_splited[++i])
	{
		inf->tmp = ft_strjoin(inf->path_splited[i], inf->input);
		if (!inf->tmp)
			return (error_allocation(data));
		if (!access (inf->tmp, F_OK))
			return (1);
		free(inf->tmp);
		inf->tmp = NULL;
	}
	command_not_found(inf->input, data);
	return (0);
}

static void	execute(t_exec_data *inf)
{
	if (execve (inf->tmp, inf->wrd_arr, inf->env_arr) < 0)
	{
		perror("minishell : execve ");
		if (inf->tmp != inf->input)
			free(inf->tmp);
		inf->tmp = NULL;
		exit(1);
	}
}

static void	check_cmd(t_exec_data *inf, t_data *data)
{
	struct stat	i_stat;

	ft_bzero(&i_stat, sizeof(i_stat));
	if (stat(inf->tmp, &i_stat) == -1)
	{
		perror("minishell: stat");
		data->exit_status = 1;
	}
	if (S_ISDIR(i_stat.st_mode))
		is_a_directory(inf->tmp, data);
	else if (!access(inf->tmp, X_OK))
		execute(inf);
	else
		access_error(inf->input, data);
}
