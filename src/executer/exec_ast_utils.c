/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:53 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/22 15:11:30 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

int	cd_arg_check(t_word *word, t_data *data)
{
	if (word->next && word->next->next
	&& word->next->next->redir == NONE)
	{
		cd_error(NULL, data, 0);
		return (0);
	}
	return (1);
}