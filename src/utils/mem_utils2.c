/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/10 09:31:00 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/parse.h"
#include "../../include/errors.h"

void	free_many(char **s1, char **s2, char **s3)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}

int	free_exp(t_data *data, t_word *word, int i)
{
	if (data->exp->new != word->word)
		free(data->exp->new);
	if (data->exp->words)
		free_strarray(data->exp->words);
	ft_bzero(data->exp, sizeof(t_expand));
	if (i)
		return (error_allocation(data));
	return (0);
}

void	free_ast(t_tree_node **root)
{
	t_tree_node	*tmp;

	tmp = *root;
	if (!tmp)
		return ;
	free_ast(&tmp->left);
	free_ast(&tmp->right);
	free_words(&tmp->word);
	free(tmp);
	root = NULL;
}

void	free_to_exit(t_data *data, t_tree_node **root)
{
	free_ast(root);
	free_env_list(data, 0, &data->env);
	free(data->home_path);
	data->home_path = NULL;
}