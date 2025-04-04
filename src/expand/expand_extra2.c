/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_extra2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-04 14:30:48 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-04 14:30:48 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	has_delimiter(char *arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (is_delimiter(*arg))
		{
			if ((*arg == ' ' && (is_delimiter(*(arg + 1)))) || *arg != ' ')
				return (1);
		}
		arg++;
	}
	return (0);
}

/*extra functions to expand_vars*/
int	get_var_val(t_data *data, int i, char **tmp)
{
	char	*name;
	t_env_node	*var;

	name = get_var_and_extra_chars(data->exp->arr[i], data);
	if (!name)
		return (-1);
	var = ft_getenv(data->env, name);
	if (var && var->val)
	{
		if (data->exp->mid)
		{
			*tmp = data->exp->mid;
			data->exp->mid = ft_strjoin(data->exp->mid, var->val);
			free(*tmp);
		}
		else
			data->exp->mid = ft_strdup(var->val);
		if (!data->exp->mid)
			return (-1);
	}
	return (0);
}

int	get_extra_chars(t_data *data, char **tmp)
{
	if (data->exp->extra)
	{
		if (data->exp->mid)
		{
			*tmp = data->exp->mid;
			data->exp->mid = ft_strjoin(data->exp->mid, data->exp->extra);
			free(*tmp);
		}
		else
			data->exp->mid = ft_strdup(data->exp->extra);
		if (!data->exp->mid)
			return (-1);
	}
	return (0);
}

char	*get_var_and_extra_chars(char *s, t_data *data)
{
	char	c;
	int	len;

	free(data->exp->buf);
	free(data->exp->extra);
	data->exp->buf = NULL;
	data->exp->extra = NULL;
	c = find_extra_var_name(s);
	if (!c)
		return (s);
	if (c)
	{
		len = ft_strlen(s) - ft_strlen(ft_strchr(s, c));
		data->exp->buf = ft_calloc(len + 1, sizeof(char));
		if (!data->exp->buf)
			return (NULL);
		ft_strlcpy(data->exp->buf, s, len + 1);
		len = ft_strlen(ft_strchr(s, c));
		data->exp->extra = ft_calloc(len + 1, sizeof(char));
		if (!data->exp->buf)
			return (NULL);
		ft_strlcpy(data->exp->extra, ft_strchr(s, c), len + 1);
	}
	return (data->exp->buf);
}

int	expand_dollar(t_data *data, char **tmp, int i)
{
	char	*exit_status;

	if (!get_var_and_extra_chars(data->exp->arr[i], data))
		return (-1);
	exit_status = ft_itoa(data->exit_status);
	if (!exit_status)
		return (-1);
	if (data->exp->mid)
	{
		*tmp = data->exp->mid;
		data->exp->mid = ft_strjoin(data->exp->mid, exit_status);
		free(*tmp);
		if (!data->exp->mid)
			return (-1);
	}
	else
		data->exp->mid = exit_status;
	return (0);
}
