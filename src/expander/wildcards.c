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

# include <sys/stat.h>

void	expand_wildcard(char *directory)
{
	DIR *dir;
	struct	dirent *entry;
	struct stat	i_stat;
	

	dir = opendir(directory);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (!stat(entry->d_name, &i_stat))
		{
			if (S_ISDIR(i_stat.st_mode) && !ft_strchr(entry->d_name, '.'))
			{
					expand_wildcard(entry->d_name);
					printf("%s ", entry->d_name);
			}
			else if (!S_ISDIR(i_stat.st_mode) && !ft_strchr(entry->d_name, '.'))
				printf("%s ", entry->d_name);
		}
		entry = readdir(dir);
	}
	write (1, "\n", 1);
}
