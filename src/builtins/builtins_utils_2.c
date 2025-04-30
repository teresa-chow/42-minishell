/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:20:25 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/30 16:30:35 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"

static char	find_sep(char *s);
static int	find_begin_of_val(char *s);
static int	find_val_len(char *word);

int	set_inf(char *word, t_input_inf *inf_arg)
{
	int		len_wrd;
	int		val_len;

	len_wrd = ft_strlen(word);
	inf_arg->sep = find_sep(word);
	inf_arg->key = ft_substr(word, 0, len_wrd - \
				ft_strlen(ft_strchr(word, inf_arg->sep)));
	if (!inf_arg->key)
		return (-1);
	if (inf_arg->sep)
	{
		inf_arg->val_strt = find_begin_of_val(word);
		val_len = find_val_len(&word[inf_arg->val_strt]);
		inf_arg->val = ft_substr(word, inf_arg->val_strt, val_len);
		if (!inf_arg->val)
		{
			free(inf_arg->key);
			inf_arg->key = NULL;
			return (-1);
		}
	}
	else
		inf_arg->val = NULL;
	return (0);
}

static int	find_begin_of_val(char *s)
{
	int	i;

	i = 0;
	while (*s && *s != '=')
	{
		s++;
		i++;
	}
	if (*s)
	{
		i++;
		s++;
		while (*s)
		{
			if (*s != '"')
				return (i);
			i++;
			s++;
		}
	}
	return (i);
}

static int	find_val_len(char *word)
{
	int	i;

	i = 0;
	while (*word && *word != '"')
	{
		i++;
		word++;
	}
	return (i);
}

static char	find_sep(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (*tmp == '+' && *(tmp + 1) == '=')
			return ('+');
		else if (*tmp == '=')
			return ('=');
		tmp++;
	}
	return (0);
}
