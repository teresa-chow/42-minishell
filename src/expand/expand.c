/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:14:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/03 15:19:39 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/expand.h"
#include "../../include/utils.h"

int	expand_vars(t_data *data);
int	get_before_aft_mid(char *arg, t_data *data);
int	handle_quotes(char *arg, t_data *data);
int	join_words(t_data *data, t_word *word);

int	expand(t_data *data, t_word *word)
{
// /////////////////////////////////////////////////////////////////	
// 		/////    TESTE    ///////
// 	t_env_node	*var;
// 	t_env_node	*var1;

// 	var = ft_getenv(data->env, "ZZ");
// 	var->val = "Hello		  World";
// 	var1 = ft_getenv(data->env, "ZA");
// 	var1->val = "Bye		World";
// 	word->word = ft_strdup("\"\"\"\"$ZZ--$ZA\"\"\"\"");
	// word->word = ft_strdup("\"$?$?$?$?$?????\"$PPWD$$$$OLDPWD$$");

// 		/////    TESTE    ///////
// //////////////////////////////////////////////////////////////////
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	if (get_before_aft_mid(word->word, data) == -1)
		return (free_exp(data, word, 1));
	if (expand_vars(data) == -1)
		return (free_exp(data, word, 1));
	if (handle_quotes(word->word, data) == -1)
		return (free_exp(data, word, 1));
	if (join_words(data, word) == -1)
		return (free_exp(data, word, 1));
	return (0);
}

int	get_before_aft_mid(char *arg, t_data *data)
{
	if (*arg != '$' || (*arg == '$' && *(arg + 1) == '$'))
	{
		if (get_before(arg, data) == -1)
			return (-1);	
	}
	if (get_after(data, arg) == -1)
		return (-1);
	if (get_mid(arg, data) == -1)
		return(-1);
	return (0);
}

int	get_invalid_part(char *tmp, t_data *data)
{
	int	i;
	char	*start;

	i = 0;
	start = tmp;
	while (*tmp == '$' && *(tmp + 1) == '$')
	{
		i++;
		tmp++;
	}
	data->exp->invalid_str = ft_calloc(i + 1, sizeof(char));
	if (!data->exp->invalid_str)
		return (-1);
	i = -1;
	while (start != tmp)
	{
		data->exp->invalid_str[++i] = *start;
		start++;
	}
	return (0);
}

int	is_valid_mid(t_data *data)
{
	char *tmp;
	int	i;

	if (!data->exp->mid)
		return (0);
	i = -1;
	tmp = data->exp->mid;
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) != '$')
			i++;
		else if ((*tmp == '$' && *(tmp + 1) == '$'))
		{
			data->exp->invalid_pos = i;
			if (get_invalid_part(tmp, data) == -1)
				return (-1);
			else
				break;
		}
		tmp++;
	}
	return (0);
}
int	set_mid(t_data *data, char **tmp)
{
	int	i;

	i = -1;
	while (data->exp->arr[++i])
	{
		if (data->exp->arr[i][0] == '?')//(ft_strchr(data->exp->arr[i], '?'))
		{
			if (expand_dollar(data, tmp, i) == -1)
				return (-1);
		}
		else if (get_var_val(data, i, tmp) == -1)
			return(-1);
		if (get_extra_chars(data, tmp) == -1)
			return(-1);
		if (data->exp->invalid_str && i == data->exp->invalid_pos)
		{
			*tmp = data->exp->mid;
			data->exp->mid = ft_strjoin(data->exp->mid, data->exp->invalid_str);
			if (!data->exp->mid)
				return (-1);
			free(*tmp);
			free(data->exp->invalid_str);
		}
	}
	return (0);
}

int	expand_vars(t_data *data)
{
	char	*tmp;

	if (is_valid_mid(data) == -1)
		return (-1);
	data->exp->arr = ft_split(data->exp->mid, '$');
	if (!data->exp->arr)
		return (-1);
	tmp = NULL;
	free(data->exp->mid);
	data->exp->mid = NULL;
	if (set_mid(data, &tmp) == -1)
		return (-1);
	return (0);
}

int	handle_quotes(char *arg, t_data *data)
{
	int	n;
	char	*to_free;

	n = count_begin_quotes(arg);
	if (n & 1)
		return (0);
	if (has_delimiter(data->exp->mid))
	{
		to_free = data->exp->mid;
		data->exp->words = get_words(data->exp->mid);
		if (!data->exp->words)
			return (-1);
		data->exp->mid = data->exp->words[0];
		if (join_with_space(data, &to_free) == -1)
			return (-1);
	}
	return (0);
}

int	join_words(t_data *data, t_word *word)
{
	free(word->word);
	if (data->exp->bfr && data->exp->aft && data->exp->mid)
		word->word = join_three(data->exp->bfr, data->exp->mid, data->exp->aft);
	else if (!data->exp->mid && (data->exp->bfr || data->exp->aft))
		word->word = ft_strjoin(data->exp->bfr, data->exp->aft);
	else if (data->exp->bfr && !data->exp->aft)
		word->word = ft_strjoin(data->exp->bfr, data->exp->mid);
	else if (data->exp->aft && !data->exp->bfr)
		word->word = ft_strjoin(data->exp->mid, data->exp->aft);
	else
	{
		if (!data->exp->mid)
			word->word = ft_strdup("");
		else
			word->word = ft_substr(data->exp->mid, 0, ft_strlen(data->exp->mid) + 1);
	}
	if (!word->word)
		return (-1);
	return (0);
}
