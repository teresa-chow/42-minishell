/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:53:06 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/24 11:41:18 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parse.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		input_processing(input);
	}
	if (input && *input)
		free(input);
	return (0);
}