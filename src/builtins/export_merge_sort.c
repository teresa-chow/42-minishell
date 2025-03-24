/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-16 11:54:54 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-16 11:54:54 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static t_env_node	*get_mid(t_env_node *head);
static t_env_node	*merge_list(t_env_node *left, t_env_node *right);

t_env_node	*sort_halfs(t_env_node *head)
{
	t_env_node	*mid;
	t_env_node	*right;
	t_env_node	*left_sort;
	t_env_node	*right_sort;

	if (!head || !head->next)
		return (head);
	mid = get_mid(head);
	right = mid->next;
	right->prev = NULL;
	mid->next = NULL;
	left_sort = sort_halfs(head);
	right_sort = sort_halfs(right);
	return (merge_list(left_sort, right_sort));
}

static t_env_node	*get_mid(t_env_node *head)
{
	t_env_node	*slow;
	t_env_node	*fast;

	slow = head;
	fast = head;
	while (fast && fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return (slow);
}

static t_env_node	*merge_list(t_env_node *left, t_env_node *right)
{
	if (!left)
		return (right);
	if (!right)
		return (left);
	if (ft_strcmp(left->key, right->key) < 0)
	{
		left->next = merge_list(left->next, right);
		left->next->prev = left;
		left->prev = NULL;
		return (left);
	}
	else
	{
		right->next = merge_list(left, right->next);
		right->next->prev = right;
		right->prev = NULL;
		return (right);
	}
}
