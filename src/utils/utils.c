/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-05 11:29:26 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-05 11:29:26 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/errors.h"

static char	*find_end(char *arg);
static int	get_home(t_data *data);

void	add_chars(char *start, char *end, char *dst)
{
	int	i;

	i = 0;
	while (start != end)
	{
		dst[i++] = *start;
		start++;
	}
}

/* Handle with HOME var*/
int	handle_with_home(t_data *data)
{
	t_env_node	*home_var;

	home_var = ft_getenv(data->env, "HOME");
	if (home_var)
	{
		data->home_path = ft_strdup(home_var->val);
		if (!data->home_path)
			return(error_allocation(data));	
	}
	else
		return (get_home(data));
	return (0);
}

static int	get_home(t_data *data)
{
	char	*tmp;
	char	*end;
	int	len;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		perror(NULL);
		return (-1);
	}
	end = find_end(tmp);
	len = end - tmp;
	data->home_path = ft_calloc(len + 1, sizeof(char));
	if (!data->home_path)
	{
		free(tmp);
		return (error_allocation(data));
	}
	add_chars(tmp, end, data->home_path);
	free(tmp);
	return (0);
}

static char	*find_end(char *arg)
{
	int	i;

	i = 0;
	while (*arg)
	{
		if (*arg == '/')
			i++;
		if (i == 3)
			break;
		arg++;
	}
	return (arg);
}