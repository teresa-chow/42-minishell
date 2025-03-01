/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:09:23 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/01 11:25:31 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static int	add_word(t_word **word_desc);
static unsigned int	substr_len(const char *str);
static int	ft_isspace(int c);

int	tokenize_w_lst(char *input, t_word_lst *word_lst)
{
	t_word		*word_desc;
	int			i;

	word_desc = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		if (!ft_isspace(input[i]))
		{
			if (!word_desc)
			{
				word_desc = malloc(sizeof(t_word));
				if (!word_desc)
				{
					word_lst = NULL;
					return (-1); // handle memory alloc error
				}
				word_lst->word = word_desc;
			}
			else
				add_word(&word_desc); // handle mem alloc error (-1)
			word_desc->word = ft_substr(input, i, substr_len(&input[i]));
			//if (!word_desc->word)
			//failed mem alloc
			i += substr_len(&input[i]);
		}
		else
			i++;
	}
	word_lst->next = NULL; // future fix: multiple commands
	free(input);
	return (0);
}

static int	add_word(t_word **word_desc)
{
	t_word	*new;

	new = malloc(sizeof(t_word));
	if (!new)
		return (-1);
	(*word_desc)->next = new;
	new->next = NULL;
	*word_desc = new;
	return (0);
}

static unsigned int	substr_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
