/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-18 14:27:25 by carlaugu          #+#    #+#             */
/*   Updated: 2025-04-18 14:27:25 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *ft_strstr(char *str, char *sub)
{
        int     i;
        int     j;

        i = -1;
        while (str[++i])
        {
                j = 0;
                while (str[i + j] == sub[j])
                {
                        if (!sub[j + 1])
                                return (&str[i]);
                        j++;
                }
        }
        return (0);
}
