/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 17:55:27 by carlaugu          #+#    #+#             */
/*   Updated: 2025-02-26 17:55:27 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static	void handle_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
}
void	cd(t_word *input)
{
	char	*path;

	if (input->next)
		path = input->next->word;
	/*TODO: if there is not word->next, means that we only have cd command, so we have to get $HOME path*/
	if (chdir(path) == -1)
		handle_error(path);
	/*TODO: we have to update PWD and OLDPWD when cd is working*/
}
