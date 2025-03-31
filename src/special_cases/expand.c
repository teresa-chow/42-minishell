/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 18:14:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025-03-30 18:14:28 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/special_cases.h"
#include "../../include/utils.h"

int	expand(t_data *data, t_word *word);

int	find_expand(t_word *word, t_data *data)
{
	char	*tmp;

	while (word)
	{
		tmp =word->word;
		while (*tmp)
		{
			if (*tmp == '$')
			{
				if (expand(data, word) == -1)
					return (-1);
				break;
			}
			tmp++;
		}
		word = word->next;
	}
	return (0);
}

int	has_many_exp(char *arg, t_data *data)
{
	while (*arg)
	{
		if (*arg == '$')
			data->exp_data->n_exp++;
		arg++;
	}
	if (data->exp_data->n_exp)
		return (1);
	return (0);
}

char	find_no_alnum(char *s)
{
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '$')
			break;
		s++;
	}
	return (*s);
}

int	check_before_and_after(char *arg, t_data *data)
{
	char	c;
	int	i;

	if (*arg != '$')
	{
		data->exp_data->before = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '$')));
		if (!data->exp_data->before)
			return (error_allocation(data)); ///////i have to free everythinbg
		data->exp_data->total_len += ft_strlen(data->exp_data->before);
	}
	c = find_no_alnum(arg);
	if (c)
	{
		i = -1;
		while (arg[++i])
		{
			if (arg[i] == c)
				break;
		}
		data->exp_data->after = ft_substr(arg, i, ft_strlen(arg) - i);
		if (!data->exp_data->after)
			return (error_allocation(data)); ///////i have to free everythinbg
		data->exp_data->total_len += ft_strlen(data->exp_data->after);
	}
	return (0);
}

int	check_many_exp(t_word *word, t_data *data)
{
	char	*tmp;
	int	i;
	char	c;
	t_env_node	*var_name;

	tmp = word->word;
	while (*tmp)
	{
		if (*tmp == '$')
			data->exp_data->n_exp++;
		tmp++;
	}
	if (data->exp_data->n_exp > 1)
	{
		data->exp_data->tokens = ft_split(word->word, '$');
		if (!data->exp_data->tokens)
			return (error_allocation(data)); //////// i have to free everything
	}
	else
		return (0);/// ??? ---- delete this
	i = -1;
	while (data->exp_data->tokens[++i])
	{
		tmp = data->exp_data->tokens[i];
		c = find_no_alnum(tmp);
		if (c)
			tmp = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, c)));
		// if (!tmp)
		var_name = get_var(data->env, tmp);
		if (c)
		{
			free(tmp);
			tmp  = NULL;
		}
		if (var_name)
		{
			if (var_name->val)
			{
				tmp = data->exp_data->tokens[i];
				data->exp_data->tokens[i] = ft_strdup(var_name->val);
				if (!data->exp_data->tokens[i])
					return (error_allocation(data)); ///// i have to free everything
				data->exp_data->total_len += ft_strlen(var_name->val);
				free(tmp);
			}
			else
			{
				free(data->exp_data->tokens[i]);
				data->exp_data->tokens[i] = ft_strdup("");
				if (!data->exp_data->tokens[i])
					return (error_allocation(data)); ///// i have to free everything
			}
		}
	}
	return (0);
}


//-------   minishell> echo olaola$PWD.?$HOME
//         olaola/home/carlaugu/42_commoncore/42-minishell/home/carlaugu.?$HOME

int	join_tokens(t_word *word, t_data *data)
{
	int	i;

	free(word->word);
	word->word = ft_calloc(data->exp_data->total_len + 1, sizeof(char));
	word->word[data->exp_data->total_len] = 0;
	if (!word->word)
		return (error_allocation(data)); ///// free everything
	if (data->exp_data->before)
		ft_strlcpy(word->word, data->exp_data->before, data->exp_data->total_len + 1);
	if (data->exp_data->tokens)
	{
		i = -1;
		while (data->exp_data->tokens[++i])
		{
			if (ft_strcmp(data->exp_data->before, data->exp_data->tokens[i]))
				ft_strlcat(word->word, data->exp_data->tokens[i], data->exp_data->total_len + 1);
		}
	}
	if (data->exp_data->var_val)
		ft_strlcat(word->word, data->exp_data->var_val, data->exp_data->total_len + 1);
	if (data->exp_data->after)
		ft_strlcat(word->word, data->exp_data->after, data->exp_data->total_len + 1);
	return (0);
}

int	expand_var_name(t_word *word, t_data *data)
{
	t_env_node	*var_name;
	char	c;
	char	*tmp;

	tmp = ft_strchr(word->word, '$') + 1;
	c = find_no_alnum(tmp);
	if (c)
		tmp = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, c)));
	// if (!tmp)
	var_name = get_var(data->env, tmp);
	if (c)
	{
		free(tmp);
		tmp  = NULL;
	}
	if (var_name)
	{
		if (var_name->val)
		{
			data->exp_data->var_val = ft_strdup(var_name->val);
			if (!data->exp_data->var_val)
				return (error_allocation(data)); //// free verything
			data->exp_data->total_len += ft_strlen(data->exp_data->var_val);
		}
	}
	return (0);
}

int	expand(t_data *data, t_word *word)
{
	data->exp_data = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp_data)
		return (error_allocation(data));
	if (check_before_and_after(word->word, data) == -1)
		return (-1);
	if (check_many_exp(word, data) == -1)
		return (-1);
	if (data->exp_data->n_exp == 1)
	{
		if(expand_var_name(word, data) == -1)
			return (-1);
	}
	if (join_tokens(word, data) == -1)
		return (-1);
	free(data->exp_data->after);
	free(data->exp_data->before);
	free(data->exp_data->var_val);
	free_strarray(data->exp_data->tokens);
	return (0);
}
