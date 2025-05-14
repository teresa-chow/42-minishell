/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:09:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/13 11:35:50 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void	print_format(int fd, char spec, char *token);

void	print_fd(int fd, const char *msg, char *token)
{
	while (*msg != '\0')
	{
		if (*msg == '%')
			print_format(fd, *(++msg), token);
		else
			write(fd, msg, 1);
		++msg;
	}
	return ;
}

static void	print_format(int fd, char spec, char *token)
{
	if (spec == 'c')
		write(fd, token, 1);
	else if (spec == 's')
		write(fd, token, ft_strlen(token));
	else
		write(fd, &spec, 1);
	return ;
}
