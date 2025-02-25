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

int	main(int ac, char **av)
{
	char	*env_var;
	char	*input;
	pid_t pid;

	(void)ac;
	env_var = getenv("PATH");
	printf("PATH: %s\n", env_var);
	while (1)
	{
		input = readline("minishell>");
		pid = fork();
		if (pid == 0)
			execve(input, av + 1, NULL);
		else
		wait(NULL);
	}
	return (0);
}
