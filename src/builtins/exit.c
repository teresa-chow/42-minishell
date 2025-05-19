/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:44:11 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/19 22:46:31 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../include/builtins.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static void	check_syntax_exit(t_word *word, t_data *data, int *many_args,
				int *syntax);
static int	check_is_digit(t_word *word, t_data *data, int *syntax);
static int	check_overflow(t_word *word, t_data *data, int *syntax);

void	exit_cmd(t_data *data, t_word *word)
{
	int		many_args;
	int		syntax_error;

	many_args = 0;
	syntax_error = 0;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	if (word)
	{
		check_syntax_exit(word, data, &many_args, &syntax_error);
		if (many_args && !syntax_error)
		{
			exit_error_many_args(data);
			return ;
		}
	}
	if (data->cd_curr)
		free(data->cd_curr);
	data->status = 0;
}

static void	check_syntax_exit(t_word *word, t_data *data, int *many_args,
	int *syntax)
{
	t_word	*tmp;
	int		count;

	count = -1;
	tmp = word;
	while (tmp)
	{
		while (tmp->redir != NONE && tmp->next)
			tmp = tmp->next->next;
		if (!tmp)
			return ;
		if (tmp->redir == NONE)
		{
			count++;
			if (count > 1)
			{
				*many_args = 1;
				break ;
			}
			data->exit_status = ft_atoi(tmp->word);
			if (count == 1 && check_is_digit(tmp, data, syntax))
				check_overflow(tmp, data, syntax);
		}
		tmp = tmp->next;
	}
}

static int	check_is_digit(t_word *word, t_data *data, int *syntax)
{
	int	i;

	i = 0;
	while (word->word[i])
	{
		if (i == 0 && (word->word[i] == '-' || word->word[i] == '+'))
			i++;
		if (!ft_isdigit(word->word[i]))
		{
			exit_error_syntax(word->word, data);
			*syntax = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_overflow(t_word *word, t_data *data, int *syntax)
{
	long	val;

	val = 0;
	val = exit_atol(word, data, syntax);
	if (!*syntax && (val < 0 || val > 255))
	{
		data->exit_status = val % 256;
		*syntax = 1;
	}
	return (0);
}
