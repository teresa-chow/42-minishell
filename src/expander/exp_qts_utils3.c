/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 16:23:30 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-07 16:23:30 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

void	update_quotes_exp_status(char *ptr, t_data *data)
{
	if (*ptr == '\'')
		data->exp->in_sing = !data->exp->in_sing;
	else if (*ptr == '"')
		data->exp->in_dbl = !data->exp->in_dbl;
	data->exp->to_exp = false;
}