/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:43:19 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/17 15:57:28 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

void	expand_wildcard(void)
{
	DIR *dir;
	struct	dirent *entry;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		printf("%s ", entry->d_name);
		entry = readdir(dir);
	}
	write (1, "\n", 1);
}
