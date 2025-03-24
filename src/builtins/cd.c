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

static	void handle_error(char *path);

// void	update_pwd_and_oldpwd(t_data *data)
// {
// 	t_env_node	*tmp;
// 	t_env_node	*old;
// 	t_env_node	*pwd;

// 	(void)old;
// 	old = get_var(data->env, "OLDPWD");
// 	pwd = get_var(data->env, "PWD");
// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->key, "OLDPWD"))
// 		{
// 			if (tmp->val)
// 				free(tmp->val);
// 			tmp->val = pwd->val;	
// 		}
// 		if (!ft_strcmp(tmp->key, "PWD"))
// 		{
// 			if (tmp->val)
// 				free(tmp->val);
// 			tmp->val = getcwd(NULL, 0);	
// 		}
// 		tmp = tmp->next;
// 	}
// }
void	cd(t_word *input, t_data *data)
{
	char	*path;

	if (input->next)
		path = input->next->word;
	/*TODO: if there is not word->next, means that we only have cd command, so we have to get $HOME path*/
	if (chdir(path) == -1)
		handle_error(path);
	update_pwd_and_oldpwd(data);
	
}

static	void handle_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
}
