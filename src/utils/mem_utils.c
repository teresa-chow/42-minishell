/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/24 09:03:51 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/parse.h"
#include "../../include/errors.h"
#include "../../include/expand.h"

void	reset_mem(t_data *data, t_tree_node **root, int i)
{
	t_env_node	*var;

	if(data->no_home)
		free(data->env_home_var);
	data->env_home_var = NULL;
	var = ft_getenv(data->env, "HOME");
	if (var)
		data->env_home_var = var->val;
	else
		data->no_home = true;
	free_ast(root);
	if (!i)
		free_env_list(data, 0, &data->env);
}

void	free_ast(t_tree_node **root)
{
	t_tree_node	*tmp;

	if (!*root)
		return ;
	tmp = *root;
	free_ast(&tmp->left);
	free_ast(&tmp->right);
	free_words(&tmp->word);
	free(tmp);
	root = NULL;
}

int	free_exp(t_data *data, int i)
{
	if (i && data->exp->words)
		free_strarray(data->exp->words);
	else
		free(data->exp->words);
	ft_bzero(data->exp, sizeof(t_expand));
	free(data->exp);
	data->exp = NULL;
	if (i)
		return (error_allocation(data));
	return (0);
}

int	free_env_list(t_data *data, int i, t_env_node **lst)
{
	t_env_node	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->val);
		free((*lst));
		(*lst) = tmp;
	}
	*lst = NULL;
	if (i)
		return (error_allocation(data));
	return (0);
}

void	free_words(t_word **word)
{
	t_word	*tmp;

	while (*word != NULL)
	{
		free((*word)->word);
		tmp = *word;
		*word = (*word)->next;
		free(tmp);
	}
}
