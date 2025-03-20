#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

int	set_exec_inf(t_exec_data *inf, t_data *data, t_word *word)
{
	ft_bzero(inf, sizeof(t_exec_data));
	if (!ft_strcmp(word->word, "."))
	{
		data->exit_status = 2;
		return (1);	
	}
	inf->wrd_arr = creat_wrd_arr(word);
	inf->env_arr = creat_env_arr(data->env);
	if (!inf->wrd_arr || !inf->env_arr)
		return (free_arrays(inf, data, 1));
	inf->env_path = set_path(data);
	if (!inf->env_path)
		return (free_arrays(inf, data, 1));
	inf->input = word->word;
	return (0);
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
int	cmd_in_env_path(t_exec_data *inf, t_data *data)
{
	int	i;

	i = -1;
	while (inf->env_path[++i])
	{
		inf->tmp = ft_strjoin(inf->env_path[i], inf->input);	
		if (!inf->tmp)
		{
			error_allocation(data);
			return (0);
		}
		if (!access(inf->tmp, F_OK))
			return (1);
		free(inf->tmp);
		inf->tmp = NULL;
	}
	command_not_found(inf->input, data);
	return (0);
}

void	execute(t_data *data, t_exec_data *inf)
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
		execve(inf->tmp , inf->wrd_arr, inf->env_arr);
	else
		waitpid(pid, &status, 0);
	free(inf->tmp);
	inf->tmp = NULL;	
	if (!status)
		data->exit_status = 0;
	else
		data->exit_status = WIFEXITED(status);
}
void	check_cmd(t_exec_data *inf, t_data *data)
{
	struct	stat	i_stat;

	ft_bzero(&i_stat, sizeof(i_stat));
	if (stat(inf->tmp, &i_stat) == -1)
	{
		perror("minishell: stat");
		data->exit_status = 1;
	}
	if (S_ISDIR(i_stat.st_mode))
		is_a_directory(inf->tmp, data);
	else if (!access(inf->tmp, X_OK))
		execute(data, inf);
	else
		access_error(inf->input, data);
}
void	exec(t_data *data, t_word *word)
{
	t_exec_data	inf;

	if (set_exec_inf(&inf, data, word))
		return ;
	if (!find_slash(inf.input))
	{
		if (cmd_in_env_path(&inf, data))
			check_cmd(&inf, data);
	}
	else
	{
		inf.tmp = inf.input;
		if (!access(inf.input, F_OK))
			check_cmd(&inf, data);
		else
			no_file_or_directory(inf.input, data);
	}
	free_arrays(&inf, data, 0);
}
