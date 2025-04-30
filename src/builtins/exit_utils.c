/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:21:08 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 16:41:54 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../include/builtins.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	handle_overflow(t_word *word, t_data *data, int *syntax);

long	exit_atol(t_word *word, t_data *data, int *syntax)
{
	int			i;
	int			sign;
	long		res;

	i = 0;
	sign = 1;
	res = 0;
	while (word->word[i] == ' ' || (word->word[i] >= 9 && word->word[i] <= 13))
		i++;
	if ((word->word[i] == '+') || (word->word[i] == '-'))
	{
		if (word->word[i] == '-')
			sign = -sign;
		i++;
	}
	while ((word->word[i] >= '0') && (word->word[i] <= '9'))
	{
		if ((sign > 0 && (res > (LLONG_MAX - (word->word[i] - '0')) / 10))
			|| (sign < 0 && (-res < (LLONG_MIN + (word->word[i] - '0')) / 10)))
			return (handle_overflow(word, data, syntax));
		res = res * 10 + word->word[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	handle_overflow(t_word *word, t_data *data, int *syntax)
{
	exit_error_syntax(word->word, data);
	*syntax = 1;
	return (0);
}