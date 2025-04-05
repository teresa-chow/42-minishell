/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/03 10:47:42 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/builtins.h"
#include "../../include/parse.h"
#include "../../include/errors.h"

void	free_many(char **s1, char **s2, char **s3)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}

void	free_strarray(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_prompt(t_prompt *prompt)
{
	if (prompt->prog)
		free(prompt->prog);
	if (prompt->usr)
		free(prompt->usr);
	if (prompt->cwd)
		free(prompt->cwd);
}

int	free_exp(t_data *data, t_word *word, int i)
{
	if (data->exp)
	{
		if (data->exp->bfr && data->exp->bfr != word->word)
			free(data->exp->bfr);
		if (data->exp->mid)
			free(data->exp->mid);
		if (data->exp->aft && data->exp->aft != word->word)
			free(data->exp->aft);
		if (data->exp->buf)
			free(data->exp->buf);
		if (data->exp->extra)
			free(data->exp->extra);
		if (data->exp->arr)
			free_strarray(data->exp->arr);
		if (data->exp->words)
			free_strarray(data->exp->words);
		free(data->exp);
		data->exp = NULL;
		if (i)
			return (error_allocation(data));
	}
	return (0);
}

int	free_env_list(t_data *data, int i, t_env_node **lst)
{
	t_env_node	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->val);
		free((*lst));
		(*lst) = tmp;
	}
	*lst = NULL;
	if (i)
		return (error_allocation(data));
	return (0);
}

void	free_words(t_word **word, t_data *data)
{
	t_word	*tmp;

	while (*word != NULL)
	{
		if (data->home_path == (*word)->word)
			data->home_path = NULL;
		free((*word)->word);
		tmp = *word;
		*word = (*word)->next;
		free(tmp);
	}
}

void	free_word_lst(t_word_lst **word_lst, t_data *data)
{
	t_word_lst	*tmp;

	while (*word_lst)
	{
		free_words(&(*word_lst)->word, data);
		tmp = *word_lst;
		*word_lst = (*word_lst)->next;
		free(tmp);
	}
}

void	free_to_exit(t_data *data, t_word_lst **word_lst)
{
	free_env_list(data, 0, &data->env);
	free(data->home_path);
	data->home_path = NULL;
	free_word_lst(word_lst, data);
}
