/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:16:37 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/29 17:52:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"

static int	create_copy(t_env_node **copy, t_data *data);
static	void	print_var_val(char *s);
static void	print_export(t_env_node *env_lst);

void	reset_inf(t_input_inf *inf)
{
	free(inf->key);
	if (inf->val)
		free(inf->val);
	inf->sep = 0;
	inf->val_strt = 0;
}

void	sort_env(t_data *data)
{
	t_env_node	*copy;

	if (!data->env)
		return ;
	copy = NULL;
	if (create_copy(&copy, data) == -1)
		return ;
	copy = sort_halves(copy);
	print_export(copy);
	free_env_list(data, 0, &copy);
	data->exit_status = 0;
}

static int	create_copy(t_env_node **copy, t_data *data)
{
	t_env_node	*tmp;
	t_env_node	*env;
	t_env_node	*last;

	last = NULL;
	env = data->env;
	while (env)
	{
		tmp = ft_calloc(sizeof(t_env_node), sizeof(char));
		if (!tmp)
			return (free_env_list(data, 1, copy));
		if (!*copy)
			*copy = tmp;
		tmp->key = ft_strdup(env->key);
		tmp->val = ft_strdup(env->val);
		if (!tmp->key || (!tmp->val && env->val))
			return (free_env_list(data, 1, copy));
		tmp->prev = last;
		if (tmp->prev)
			tmp->prev->next = tmp;
		last = tmp;
		env = env->next;
	}
	return (0);
}

static	void	print_var_val(char *s)
{
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
}

static void	print_export(t_env_node *env_lst)
{
	while (env_lst)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_lst->key, STDOUT_FILENO);
		if (env_lst->val)
		{
			if (env_lst->val[0])
			{
				write (STDOUT_FILENO, "=", 1);
				print_var_val(env_lst->val);
			}
		}
		write(STDOUT_FILENO, "\n", 1);
		env_lst = env_lst->next;
	}
}
