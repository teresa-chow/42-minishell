/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 17:55:27 by carlaugu          #+#    #+#             */
/*   Updated: 2025-02-26 17:55:27 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"

void	cd(char **input)
{
	(void)input;
	char	*buf;

	if (chdir(input[1]) == 0)
	{
		buf = getcwd(NULL, 0);
		printf ("Now, we are in the %s!\n", buf);
		free(buf);
	}
	else
		printf("Fail!\n");
}