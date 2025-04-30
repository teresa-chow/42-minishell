/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                   		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:29:26 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/08 15:03:41 by tchow-so         ###   ########.fr       */
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

char	*join_three(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	if (s2)
		ft_strlcat(dst, s2, len + 1);
	if (s3)
		ft_strlcat(dst, s3, len + 1);
	return (dst);
}

/* Handle with HOME var*/
int	handle_with_home(t_data *data)
{
	if (!data->env_home_var)
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
	data->env_home_var = ft_calloc(len + 1, sizeof(char));
	if (!data->env_home_var)
	{
		free(tmp);
		return (error_allocation(data));
	}
	add_chars(tmp, end, data->env_home_var);
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