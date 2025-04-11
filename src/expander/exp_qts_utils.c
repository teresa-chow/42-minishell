/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 23:02:03 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-10 23:02:03 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

/* This is an auxiliary function for get_var_len  and  get_var_val*/
void	temp_string_change(char **ptr, char **inval, char *box, bool end)
{
	if (!end)
	{
		*inval = find_non_alnum(*ptr);
		*box = **inval;
		**inval = 0;
	}
	if (end)
	{
		**inval = *box;
		*ptr = *inval;
	}
}