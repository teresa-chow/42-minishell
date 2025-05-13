/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/13 14:55:32 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/expand.h"

void	error_cd(t_data *data)
{
	print_fd(2, "minishell: cd: HOME not set\n", NULL);
	data->exit_status = ERR;
}