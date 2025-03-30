/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 18:16:46 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-30 18:16:46 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/special_cases.h"

int	find_expansion(t_word *word, t_data *data);

int	check_special_cases(t_data *data, t_word_lst *word_lst)
{
	// t_env_node	*delete;
	// t_env_node	*delete2;

	// delete = get_var(data->env, "ZZ");
	// delete->val = "hello       world";
	// delete2 = get_var(data->env, "ZA");
	// delete2->val = "Ola      Carlos";
	if (find_expansion(word_lst->word, data) == -1)
		return (-1);
	return (1);
}

t_word	*find_last(t_word *word, t_word *curr)
{
	while (word)
	{
		if (word == curr)
			break;
		if (word->next == curr)
			break;
		word = word->next;
	}
	return (word);
}

int	find_expansion(t_word *word, t_data *data)
{
	char	*arg;
	int	check;
	t_word	*last_word;
	t_word	*tmp;

	last_word = word;
	arg = NULL;
	tmp = word;
	while (tmp)
	{
		arg = tmp->word;
		check = analyze_arg(arg, data);
		if (check == -1)
			return (-1);
		else if (check)
		{
			if (data->exp_data->has_quotes)
				data->exp_data->prev_arg = find_last(word, tmp);
			else
				data->exp_data->prev_arg = last_word;
			data->exp_data->next_arg = tmp->next;
			expand(data, tmp);
			tmp = data->exp_data->next_arg;
		}
		else
		{
			last_word = tmp;
			tmp = tmp->next;
		}
	}
	return (0);
}
