/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:11:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/25 15:13:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

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
		read_input();
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
