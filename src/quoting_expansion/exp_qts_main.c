/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_qts_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 16:25:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-07 16:25:40 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	handle_arg(t_word *word, t_data *data);
static int	handle_normal(char **ptr, t_data *data);

int	build_new(t_data *data, char *bgn, char *end, int len);
int	handle_exp_qts(char **ptr, t_data *data);

int	analyze_args(t_word *word, t_data *data)
{
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	while (word)
	{
		check_special_char(word->word, data);
		if (data->exp->has_dbl || data->exp->has_sing || data->exp->has_exp)
		{
			if (handle_arg(word, data) == -1)
				return(free_exp(data, word, 1));
			free(word->word);
			word->word = data->exp->new;
		}
		reset_checkers(data);
		free_exp(data, word, 0);
		word = word->next;
	}
	return (0);
}

static int	handle_arg(t_word *word, t_data *data)
{
	char	*ptr;
	int	i;

	ptr = word->word;
	while (*ptr)
	{
		if (*ptr == '\'' || *ptr == '"')
			i = handle_exp_qts(&ptr, data);
		else
			i = handle_normal(&ptr, data);
		if (i == -1)
			return (-1);
	}
	return (0);
}

/////////////////   TO FINISH ////////////////////////////////

void	join_splited_words(t_data *data, char **tmp)
{
	int	i;
	int	j;

	i = -1;
	while (data->exp->words[++i])
	{
		j = -1;
		while (data->exp->words[i][++j])
			*(*tmp)++ = data->exp->words[i][j];
		if (data->exp->words[i + 1])
			*(*tmp)++ = ' ';
	}
}

int	get_split_words(t_data *data, char **ptr, char **tmp)
{
	char	*inval;
	char	box;
	t_env_node	*var;

	if (data->exp->words)
	{
		free_strarray(data->exp->words);
		data->exp->words = 0;
	}
	(*ptr)++;
	inval = find_non_alnum(*ptr);
	box = *inval;
	*inval = 0;
	var = ft_getenv(data->env, *ptr);
	if (var)
	{
		data->exp->words = get_words(var->val);
		if (!data->exp->words)
			return (-1);
		join_splited_words(data, tmp);
	}
	*inval = box;
	*ptr = inval;
	return (0);
}

static int	handle_normal(char **ptr, t_data *data)
{
	int	len;
	char	*end;
	char	*tmp;
	char	*start;

	(void)start;
	end = get_next_qt(*ptr, data);
	len = get_len(*ptr, end, data);
	tmp = ft_calloc(len + 1, sizeof(char));
	start = tmp;
	if (!tmp)
		return (-1);
	while (*ptr != end)
	{
		if (**ptr == '$' && is_valid_dollar(*ptr))
			get_split_words(data, ptr, &tmp);
		else
			*tmp++ = *(*ptr)++;
	}
	build_new(data, start, tmp, len);
	return (0);
}

int	build_new(t_data *data, char *bgn, char *end, int len)
{
	int	total;
	char	*to_free;

	total = ft_strlen(data->exp->new) + len + 1;
	to_free = data->exp->new;
	data->exp->new = ft_calloc(total, sizeof(char));
	if (!data->exp->new)
		return (-1);
	if (to_free)
	{
		ft_strlcpy(data->exp->new, to_free, total);
		add_chars(bgn, end, ft_strchr(data->exp->new, 0));
	}
	else
		add_chars(bgn, end, data->exp->new);
	free(to_free);
	return (0);
}

// int	fill_with_dbl_quotes()
// {

// }

int	handle_exp_qts(char **ptr, t_data *data)
{
	int	i;
	int	len;
	char	*end;

	update_quotes_exp_status(*ptr, data);
	end = get_next_qt(*ptr + 1, data);
	len = get_len(*ptr + 1, end,data);
	if (!data->exp->to_exp)
		i = build_new(data, *ptr + 1, end, len);
	// else
	// 	 i = fill_with_dbl_quotes();
	if (i == -1)
		return (-1);
	update_quotes_exp_status(end, data);
	if (*end)
		*ptr = end + 1; ///// this is equal to others ---handle_normal();
	else
		*ptr = end;
	return (0);
}
