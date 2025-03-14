/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:20:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/14 18:20:27 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

static t_tree_node	*new_node(int val, char *str);

static t_tree_node	*new_node(int val, char *str)
{
	t_tree_node	*new;
	new = ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	//new->val = val;
	//new->str = ft_strdup(str);
	return(new);
}

static void print_depth_first(t_tree_node *root) //tmp function
{
	t_tree_node	*process_stack[100];
	size_t		process_stack_num = 0;
	
	process_stack[0] = root;
	process_stack_num++;
	while (process_stack_num > 0)
	{
		t_tree_node	*current = process_stack[process_stack_num - 1];
		process_stack_num--;
		printf("%d ", current->val);
		if (current->right != NULL)
		{
			process_stack[process_stack_num] = current->right;
			process_stack_num++;
		}
		if (current->left != NULL)
		{
			process_stack[process_stack_num] = current->left;
			process_stack_num++;
		}
	}
}