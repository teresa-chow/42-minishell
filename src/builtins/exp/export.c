#include "../../../include/builtins.h"
#include "../../../include/utils.h"

char	find_sep(char *s)
{
	while (*s)
	{
		if (*s == '+' && *(s + 1) == '=')
			return ('+');
		else if (*s == '+' && *(s + 1) != '=')
			return (0);
		s++;
	}
	return ('=');
}

int	exist_var(t_env_node *env, t_ipt_inf *inf_arg)
{
	char	*key;
	
	while (env)
	{
		key = ft_substr(env->var, 0, ft_strlen(env->var) - ft_strlen(ft_strchr(env->var, '=')));
		if (!key)
			return (-1);
		if (!ft_strcmp(key, inf_arg->key))
		{
		
		}
		env = env->next;
	}
	return (0);
}

// static t_env_node	*get_last(t_env_node *env_lst)
// {
// 	while (env_lst)
// 	{
// 		if (!env_lst->next)
// 			break;
// 		env_lst = env_lst->next;
// 	}
// 	return (env_lst);
// }
int	reset_inf(char *word, t_ipt_inf *inf_arg)
{
	inf_arg->sep = find_sep(word);
	inf_arg->key = ft_substr(word, 0, ft_strlen(word) - ft_strlen(ft_strchr(word, inf_arg->sep)));
	if (!inf_arg->key)
		return (-1);
	inf_arg->val_strt = ft_strlen(word) - ft_strlen(ft_strchr(word, '='));
	inf_arg->val = ft_substr(word, inf_arg->val_strt, ft_strlen(ft_strchr(word, '=')));
	if (!inf_arg->val)
	{
		free(inf_arg->key);
		return (-1);
	}
	return (0);
}

void	export(t_word *word_lst, t_env_node **env_lst)
{
	t_ipt_inf	inf_arg;

	if (!word_lst->next)
	{
		sort_env(*env_lst);
		print_export(*env_lst);
	}
	else
	{
		word_lst = word_lst->next;
		while (word_lst)
		{
			if (reset_inf(word_lst->word, &inf_arg) == -1)
				return ;
			if (exist_var(*env_lst, &inf_arg) == -1)
				return;
			else
				add_var();
			// free_inf_arg to reset the info ???????
		}
	}
}
