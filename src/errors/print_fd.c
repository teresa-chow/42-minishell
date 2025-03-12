/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:09:39 by tchow-so          #+#    #+#             */
/*   Updated: 2024/03/29 15:26:13 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"

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
