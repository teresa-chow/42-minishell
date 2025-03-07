#include "../../../include/utils.h"
#include "../../../include/parse.h"

static	t_env_node	*find_in_env(t_env_node **env_lst, char	*word)
{
	t_env_node	*tmp;
	char	**var;

	tmp = *env_lst;
	while (tmp)
	{
		var = ft_split(tmp->var, '=');
		// if (!var)
		if (!ft_strcmp(var[0], word))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				*env_lst = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free_strarray(var);
			return (tmp);
		}
		free_strarray(var);
		tmp = tmp->next;
	}
	return (tmp);
}

void	unset(t_env_node **env_lst, t_word *word_lst)
{
	t_env_node	*tmp;
	
	while (word_lst)
	{
		tmp = *env_lst;
		tmp = find_in_env(env_lst, word_lst->word);
		if (tmp)
			free(tmp);
		word_lst = word_lst->next;
	}
}