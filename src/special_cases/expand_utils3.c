/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:19:45 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/03 14:40:20 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/special_cases.h"
#include "../../include/utils.h"

/*extra function to get_var_val to expand_vars*/
char	*get_var_and_extra_chars(char *s, t_data *data)
{
	char	c;
	int	len;

	free(data->exp->buf);
	free(data->exp->extra);
	data->exp->buf = NULL;
	data->exp->extra = NULL;
	c = find_extra(s);
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
/*extra functions to handle_quotes*/
int	count_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '"')
			break;
	}
	return (i);
}

int	join_with_space(t_data *data, char **to_free)
{
	int	i;

	i = 0;
	while (data->exp->words[++i])
	{
		data->exp->mid = join_three(data->exp->mid, " ", data->exp->words[i]);
		if (!data->exp->mid)
			return (-1);
		free(*to_free);
		*to_free = data->exp->mid;
	}
	return (0);
}
/*extra functions to join_words function*/
char	*join_three(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, len + 1);
	ft_strlcat(dst, s3, len + 1);
	return (dst);
}