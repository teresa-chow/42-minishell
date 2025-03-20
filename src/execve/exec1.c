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

int	is_valid_cmd(t_data *data, char *input)
{
	char	**env_path;
	int	i;
	char	*tmp;

	env_path = set_path(data);
	if (!env_path)
		return ;
	i = -1;
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], input);
		if (!tmp)
			return (error_allocation(data));
	}
	// free_arrays
	return (0);
}

// void	check_status(t_data *data)
// {
// 	if (data->exit_status == ERR_F)

// }

void	exec(t_data *data, t_word *word)
{
	data->wrd_arr = creat_wrd_arr(word);
	data->env_arr = creat_env_arr(data->env);
	if (!data->wrd_arr || !data->env_arr)
	{
		free_arrays(data, 1);
		return ; 
	}
	if (!find_slash(word->word))
	{	
		is_valid_cmd(data, word->word);
		check_status(data);
			command_not_found(word->word, data);
	}
	free_arrays(data, 0);
}
