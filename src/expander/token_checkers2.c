/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checkers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 23:07:30 by carlaugu          #+#    #+#             */
/*   Updated: 2025-05-02 23:07:30 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

void	check_builtin_name(t_data *data, t_word **word)
{
	if (!ft_strcmp((*word)->word, "export"))
		data->exp->export_cmd = true;
	if (!ft_strcmp((*word)->word, "cd"))
		data->exp->cd_cmd = true;
}
