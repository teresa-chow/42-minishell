/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils22.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-04 14:15:53 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-04 14:15:53 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

int	count_no_quotes(char *start, char *end)
{
	int	i;

	i = 0;
	while (start != end)
	{
		if (*start != '"')
			i++;
		start++;
	}
	return (i);
}

void	add_no_quotes(char *dst,char *start, char *end)
{
	int	i;

	i = 0;
	while (start != end)
	{
		if (*start != '"')
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
	ft_strlcat(dst, s2, len + 1);
	ft_strlcat(dst, s3, len + 1);
	return (dst);
}