/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/07 14:58:05 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/parse.h"
#include "../../include/errors.h"

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

void	free_to_exit(t_data *data, t_tree_node **node)
{
    (void)node; //tmp
	free_env_list(data, 0, &data->env);
	free(data->home_path);
	data->home_path = NULL;
	free(data->exp);
	//TODO: free ast tree
}