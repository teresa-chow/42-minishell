/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:04:20 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 15:01:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/errors.h"

static int	check_syntax(char *s, t_data *data, int *exit);

void	handle_with_args(t_word *word, t_data *data, int *exit)
{
	t_input_inf	inf_arg;

	ft_bzero(&inf_arg, sizeof(t_input_inf));
	while (word)
	{
		if (word->redir != NONE)
		{
			data->has_redir = true;
			word = word->next;
		}
		else if (check_syntax(word->word, data, exit))
		{
			data->has_vars = true;
			if (set_inf(word->word, &inf_arg) == -1)
			{
				error_allocation(data);
				return ;
			}
			if (add_var(&inf_arg, data) == -1)
				return ;
		}
		word = word->next;
	}
	if (data->has_redir && !data->has_vars)
		sort_env(data);
}

static int	check_syntax(char *s, t_data *data, int *exit)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	if ((s && ft_isdigit(*s)) || *s == '=')
	{
		if (*exit == -1)
			*exit = ERR;
		error_export_syntax(s, data);
		return (0);
	}
	while (*tmp)
	{
		if ((*tmp == '+' && *(tmp + 1) == '=') || *tmp == '=')
			break ;
		if (!ft_isalnum(*tmp) && *tmp != '_')
		{
			if (*exit == -1)
				*exit = ERR;
			error_export_syntax(s, data);
			return (0);
		}
		tmp++;
	}
	return (1);
}
