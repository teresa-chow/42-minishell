/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_analyze_dir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/05/14 15:04:27 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expand.h"

static int	stat_check(struct dirent *entry, struct stat *i_stat, t_data *data);

int	check_directory(struct dirent *entry, char *s, bool *check, t_data *data)
{
	struct stat	i_stat;
	char		*str;

	if (entry->d_name[0] != '.' && s[ft_strlen(s) - 1] == '/')
	{
		ft_bzero(&i_stat, sizeof(i_stat));
		if (stat_check(entry, &i_stat, data) == -1)
			return (-1);
		str = ft_substr(s, 0, ft_strlen(s) - 1);
		if (is_matching_pattern(str, entry->d_name, data))
		{
			if (S_ISDIR(i_stat.st_mode))
			{
				*check = true;
				data->wild->print_dir = true;
			}
		}
		free(str);
	}
	return (0);
}

static int	stat_check(struct dirent *entry, struct stat *i_stat, t_data *data)
{
	if (stat(entry->d_name, i_stat) == -1)
	{
		perror("minishell: stat");
		data->exit_status = ERR;
		return (-1);
	}
	return (0);
}