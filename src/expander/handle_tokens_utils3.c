/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:23:37 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/19 16:38:54 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	set_tmp(char **tmp, char **start, int len)
{
	*tmp = ft_calloc(len + 1, sizeof(char));
	if (!*tmp)
		return (-1);
	*start = *tmp;
	return (0);
}
