#include "../../../include/utils.h"
#include "../../../include/parse.h"

static	t_env_node	*find_in_env(t_env_node **env_lst, char	*word)
{
	char	**var;
	t_env_node	*last;
	t_env_node	*tmp;

	last = NULL;
	tmp = *env_lst;
	while (tmp)
	{
		var = ft_split(tmp->var, '=');
		// if (!var)
		if (ft_strcmp(var[0], word) != 0)
			free_strarray(var);
		else
		{
			if (last)
				last->next = tmp->next;
			else
				*env_lst = tmp->next;
			free_strarray(var);
			return (tmp);
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

void	unset(t_env_node **env_lst, t_word *word_lst)
{
	t_env_node	*tmp;
	t_env_node	*box;
	
	(void)box;
	while (word_lst)
	{
		tmp = *env_lst;
		tmp = find_in_env(env_lst, word_lst->word);
		if (tmp)
		{
			box = tmp->next;
			free(tmp);
		}
		word_lst = word_lst->next;
	}
}