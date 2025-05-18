/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:34:29 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/18 19:35:56 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/expand.h"
#include "../../include/execute.h"
#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

int	is_builtin_cmd(t_word *word)
{
	t_word	*tmp;

	tmp = word;
	while (tmp && tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!tmp)
		return (0);
	if (!ft_strcmp(tmp->word, "echo")
		|| !ft_strcmp(tmp->word, "cd")
		|| !ft_strcmp(tmp->word, "pwd")
		|| !ft_strcmp(tmp->word, "export")
		|| !ft_strcmp(tmp->word, "unset")
		|| !ft_strcmp(tmp->word, "env")
		|| !ft_strcmp(tmp->word, "exit"))
		return (1);
	return (0);
}

void	exec_builtin_cmd(t_data *data, t_word *word)
{
	t_word	*tmp;

	tmp = word;
	while (tmp->redir != NONE)
		tmp = tmp->next->next;
	if (!ft_strcmp(tmp->word, "echo"))
		echo(tmp, data);
	else if (!ft_strcmp(tmp->word, "cd"))
	{
		if (!cd_arg_check(tmp, data))
			return ;
		cd(tmp, data);
	}
	else if (!ft_strcmp(tmp->word, "pwd"))
		pwd(data);
	else if (!ft_strcmp(tmp->word, "export"))
		export(data, tmp);
	else if (!ft_strcmp(tmp->word, "unset"))
		unset(data, tmp->next);
	else if (!ft_strcmp(tmp->word, "env"))
		env_cmd(data->env, data);
	else if (!ft_strcmp(tmp->word, "exit"))
		exit_cmd(data, tmp);
}
