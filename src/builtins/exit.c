/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:44:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/07 14:59:40 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static void	check_syntax_exit(t_word *word, t_data *data, int *many_args,
	int *syntax);

void	exit_cmd(t_data *data, t_tree_node **node, int *i)
{
	free_to_exit(data, node);
	*i = 0;
}

static void	check_syntax_exit(t_word *word, t_data *data, int *many_args,
	int *syntax)
{
	char	*tmp;

	tmp = NULL;
	if (word->next)
	{
		tmp = word->next->word;
		if (word->next->next)
			*many_args = 1;
		data->exit_status = ft_atoi(word->next->word);
	}
	while (tmp && *tmp)
	{
		if (!ft_isdigit(*tmp))
		{
			exit_error_syntax(word->next->word, data);
			*syntax = 1;
			break ;
		}
		tmp++;
	}
}

void	check_exit_args(t_data *data, t_tree_node **node, int *i)
{
	int		many_args;
	int		syntax_error;

	many_args = 0;
	syntax_error = 0;
	check_syntax_exit((*node)->word, data, &many_args, &syntax_error);
	if (many_args && !syntax_error)
	{
		exit_error_many_args(data);
		return ;
	}
	exit_cmd(data, node, i);
}
