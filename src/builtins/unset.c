#include "../../../include/utils.h"
#include "../../../include/parse.h"
#include "../../../include/errors.h"

static int	update_env(t_env_node **env, t_env_node *tmp, char *key)
{
	free(key);
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	else
		*env = tmp->next;
	free(tmp);
	return (0);
}

static int	clean_env(t_env_node **env, char *word)
{
	t_env_node	*tmp;
	char	*key;

	tmp = *env;
	while (tmp)
	{
		key = ft_substr(tmp->var, 0, ft_strlen(tmp->var) - ft_strlen(ft_strchr(tmp->var, '=')));
		if (!key)
			return(error_allocation());
		if (!ft_strcmp(key, word))
			return(update_env(env, tmp, key));
		free(key);
		tmp = tmp->next;
	}
	return (0);
}

void	unset(t_env_node **env_lst, t_word *word_lst)
{
	while (word_lst)
	{
		if (clean_env(env_lst, word_lst->word) == -1)
			return ;
		word_lst = word_lst->next;
	}
}
