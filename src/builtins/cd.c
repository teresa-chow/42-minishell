/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/30 14:01:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/parse.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/expand.h"

static	int	update_pwd_and_oldpwd(t_data *data);
static void	handle_old(t_env_node *old, t_env_node *pwd, char *curr);

void	cd(t_word *input, t_data *data)
{
	char	*to_exec;

	to_exec = NULL;
	if (input->next && input->next->word)
		to_exec = input->next->word;
	else
	{
		if (!data->env_home_var)
		{
			print_fd(2, "minishell: cd: HOME not set\n", NULL);
			data->exit_status = 1;
			return ;
		}
		to_exec = data->env_home_var;
	}
	if (data->has_hifen && !ft_strcmp("-", to_exec))
	{
		print_fd(STDERR_FILENO, "minishell: OLDPWD not set\n", NULL);
		data->exit_status = 1;
		return ;
	}
	else if (data->has_hifen)
		ft_putendl_fd(to_exec, STDOUT_FILENO);
	if (chdir(to_exec) == -1)
	{
		cd_error(to_exec, data, 1);
		return ;
	}
	if (!update_pwd_and_oldpwd(data))
		data->exit_status = 0;
	else
		data->exit_status = 1;
}

static int	update_pwd_and_oldpwd(t_data *data)
{
	t_env_node	*old;
	t_env_node	*pwd;
	static char	*curr;

	old = ft_getenv(data->env, "OLDPWD");
	pwd = ft_getenv(data->env, "PWD");
	handle_old(old, pwd, curr);
	if (pwd)
	{
		if (!old || !old->val)
			free(pwd->val);
		pwd->val = getcwd(NULL, 0);
		if (!pwd->val)
		{
			perror("minishell");
			return (1);
		}
	}
	else
		curr = getcwd(NULL, 0);
	return (0);
}

static void	handle_old(t_env_node *old, t_env_node *pwd, char *curr)
{
	if (old)
	{
		if (old->val)
			free(old->val);
		old->val = NULL;
		if (pwd && pwd->val)
			old->val = pwd->val;
		else
			old->val = curr;
	}
}
