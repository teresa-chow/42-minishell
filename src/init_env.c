#include "../include/utils.h"

int	init_env_lst(char **envp, t_env_node **env_lst)
{
	int	i;
	t_env_node	*tmp;
	t_env_node	*last;

	i = -1;
	last = NULL;
	while (envp[++i])
	{
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
		{
			free_env_list(*env_lst);
			return (0);
		}
		tmp->var = ft_strdup(envp[i]);
		if (last)
			last->next = tmp;
		if (!*env_lst)
			*env_lst = tmp;
		last = tmp;
	}
	return (1);
}