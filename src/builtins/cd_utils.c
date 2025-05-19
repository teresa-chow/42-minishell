/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/19 10:29:30 by carlaugu         ###   ########.fr       */
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

void	get_cd_curr(t_data *data, t_env_node *old, t_env_node *pwd)
{
	data->cd_curr = getcwd(NULL, 0);
	if (!pwd && !old)
	{
		free(data->cd_curr);
		data->cd_curr = NULL;
	}
}
