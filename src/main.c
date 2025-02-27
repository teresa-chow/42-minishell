/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 14:09:36 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/execve.h"

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	(void)argc;
	(void)argv;
	path = get_path(envp);
	if (path)
		printf("%s\n", path);
	while (1)
	{
		read_input(envp);
	}
	return (0);
}

/*
pid = fork();
if (pid == 0)
	execve(input, av + 1, NULL);
else
wait(NULL);
*/
