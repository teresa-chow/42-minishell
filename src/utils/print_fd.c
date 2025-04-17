/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:09:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/17 11:04:38 by tchow-so         ###   ########.fr       */
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
	{
		while (*token)
			write(fd, token++, 1);
	}
	else
		write(fd, &spec, 1);
	return ;
}
