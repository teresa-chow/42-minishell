/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:20:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/21 16:40:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

void	create_syntax_tree(t_word_lst *word_lst, t_tree_node **root)
{
	(void)word_lst;
	(void)root;

	//find lower precedence op
	//if no op -- single cmd -- single node
	//check if parentheses
}

/*
sample tree

		  0
	1			2
3		4	5		6

*/

/*
Sample : depth-first search (DFS) 0 1 3 4 2 5 6 -- stack data structure
traverses from root and proceeds through the nodes as far as possible until
we reach the node with no unvisited nodes nearby
>> builds the tree sub-tree by sub-tree
LIFO
- inorder traversal : left-root-right
- preorder traversal : root-left-right
- postorder traversal : left-right-root
*/
/*static void print_depth_first(t_tree_node *root) //tmp function
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
		if (current->val == 4)
		{
			printf("Found node %d (4)\n", current->val);
			break ;
		}
		else
			printf("Not yet: %d\n", current->val);
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
}*/

/*
recursive -- less efficient: more call stacks
to exit: int found 0 or 1 (if 1 return),
return after condition wouldn't suffice
*/
/*static void print_depth_first_rec(t_tree_node *node) //tmp function
{
	printf("%d ", node->val); //any action needed instead of printing
	if (node->left != NULL)
		print_depth_first_rec(node->left);
	if (node->right != NULL)
		print_depth_first_rec(node->right);
}*/

/*
Sample : breadth-first search (BFS) 0 1 2 3 4 5 6 -- queue data structure
traverses tree level by level
FIFO
*/