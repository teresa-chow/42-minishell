/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 08:40:35 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 11:05:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long	ft_len_num(long n)
{
	long	i;

	i = 0;
	if (n >= 0 && n <= 9)
		return (1);
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static	void	ft_char(char *str, long n, int len)
{
	if (n == 0)
		str[len] = '0';
	while (n > 0)
	{
		str[len--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char		*str;
	long long	num;
	int			len;
	int			is_neg;

	num = n;
	is_neg = (num < 0);
	if (is_neg)
		num = -num;
	len = ft_len_num(num) + is_neg;
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (is_neg)
		str[0] = '-';
	ft_char(str, num, len - 1);
	return (str);
}
