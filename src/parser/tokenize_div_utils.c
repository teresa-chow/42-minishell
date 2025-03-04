/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_div_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:58:16 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/04 13:58:16 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static int	add_word(t_word **word_desc);
static unsigned int	substr_len(const char *str);
static unsigned int	next_quote(const char *str, int	code);

int	handle_other(char *cmd, int *j, t_word_lst *word_lst, t_word **word)
{
	if (!*word)
	{
		*word = malloc(sizeof(t_word)); //handle mem_alloc err
		if (!*word)
		{
			word_lst = NULL;
			return (-1);
		}
		(*word)->next = NULL;
		word_lst->word = *word;
	}
	else
	{
		if (add_word(word) == -1) //handle mem_alloc err
			return (-1);
	}
	(*word)->word = ft_substr(cmd, *j, substr_len(cmd)); // not working 3rd parcel (cause: substrlen handling of delimiters)
	ft_printf("utils :: cmd: %s\n", cmd);
	ft_printf("utils :: word: %s\n", (*word)->word);
	if (!(*word)->word)
		return (-1);
	*j += substr_len(cmd);
	ft_printf("j: %d\n", *j);
	sleep(3);
	return (0);
}

int	handle_quote(char *cmd, int *j, t_word_lst *word_lst, t_word **word) //
{
	if (!*word)
	{
		*word = malloc(sizeof(t_word)); //handle mem_alloc err
		if (!*word)
		{
			word_lst = NULL;
			return (-1);
		}
		word_lst->word = *word;
	}
	else
	{
		if (add_word(word) == -1) //handle mem_alloc err
			return (-1);
	}
	(*word)->word = ft_substr(cmd, *j, next_quote(cmd, is_quote(cmd[*j])));
	if (!(*word)->word)
		return (-1);
	j += next_quote(&cmd[*j], is_quote(cmd[*j]));
	return (0);
}

static int	add_word(t_word **word_desc)
{
	t_word	*new;

	new = malloc(sizeof(t_word));
	if (!new)
		return (-1);
	new->next = NULL;
	(*word_desc)->next = new;
	*word_desc = (*word_desc)->next;
	return (0);
}

static unsigned int	substr_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && (!is_delimiter(str[i])))
		i++;
	return (i);
}

static unsigned int	next_quote(const char *str, int	code)
{
	unsigned int	i;

	i = 0;
	if (code == 1)
	{
		while (str[i] && (str[i] != '\''))
			i++;
	}
	else if (code == 2)
	{
		while (str[i] && (str[i] != '\"'))
			i++;
	}
	return (i);
}
