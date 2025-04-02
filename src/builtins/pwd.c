/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-04 22:28:24 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-04 22:28:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("minishell");
		data->exit_status = 1;
	}
	else
	{
		ft_printf ("%s\n", path);
		free(path);
		data->exit_status = 0;
	}
}
