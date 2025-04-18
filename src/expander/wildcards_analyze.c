/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_analyze.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-18 17:34:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-18 17:34:28 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static char	find_last_char(char *s);
static int      take_out_asterisk(char *s, t_data *data);

/*TODO: free data.exp.wild_substr*/
int	handle_wildcard(char *s, t_data *data)
{
	char	*ch;
	char	first_ch;
	char	last_ch;

	ch = ft_strchr(s, '*');
	if (!ch)
		return (0);
	first_ch = *s;
	last_ch = find_last_char(s);
	if (first_ch == '*' && last_ch != '*')
		data->exp->aft_wild = true;
	else if (first_ch != '*' && last_ch == '*')
		data->exp->bfr_wild = true;
	else if (first_ch == '*' && last_ch == '*')
		data->exp->mid_wild = true;
	if (take_out_asterisk(s, data) == -1)
                return (-1);
        // expand_wildcard();
	return (0);
}

static char	find_last_char(char *s)
{
	while (*s)
		s++;
	return (*(s - 1));
}

static int      take_out_asterisk(char *s, t_data *data)
{
	if (data->exp->bfr_wild)
		data->exp->wild_substr = ft_substr(s, 0, ft_strlen(s) 
                - ft_strlen(ft_strchr(s, '*')));
	else if (data->exp->aft_wild)
                data->exp->wild_substr = ft_substr(s, 1, ft_strlen(s + 1));
	else if (data->exp->mid_wild)
                data->exp->wild_substr = ft_substr(s, 1, ft_strlen(s + 1)
                - ft_strlen(ft_strchr(s + 1, '*')));
	if (!data->exp->wild_substr)
                return (-1);
}
