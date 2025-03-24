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

#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"

static	void	update_pwd_and_oldpwd(t_data *data);

void	cd(t_word *input, t_data *data)
{
	char	*path;

	path = NULL;
	if (input->next)
		path = input->next->word;
	// else
	// 	expan()
	if (chdir(path) == -1)
	{
		cd_error(path, data);
		return ;
	}
	update_pwd_and_oldpwd(data);
}

static void	update_pwd_and_oldpwd(t_data *data)
{
	t_env_node	*old;
	t_env_node	*pwd;

	old = get_var(data->env, "OLDPWD");
	pwd = get_var(data->env, "PWD");
	if (old)
	{
		if (old->val)
			free(old->val);
		old->val = NULL;
		if (pwd && pwd->val)
			old->val = pwd->val;
	}
	if (pwd)
	{
		if (!old || !old->val)
			free(pwd->val);
		pwd->val = getcwd(NULL, 0);
		if (!pwd->val)
		{
			perror("minishell: ");
			data->exit_status = 1;
			pwd->val = NULL;
		}
	}
}
