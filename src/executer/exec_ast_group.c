/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:57:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/18 19:40:22 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/struct.h"

void	ast_handle_group(t_data *data, t_tree_node **node)
{
	ast_depth_search(data, &(*node)->left, 0);
	ast_depth_search(data, &(*node)->right, 0);
	return ;
}
