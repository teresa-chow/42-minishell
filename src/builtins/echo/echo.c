/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:57:47 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 14:06:00 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/parse.h"

/* TODO: fix echo with no arguments */
void	echo(t_word_lst *input)
{
	int	flag;
	t_word	*start;
	
	if (input->word->next)
	  flag = input->word->next->flags;
	if (flag == 2)
		start = input->word->next->next;
	else
		start = input->word->next;
	while (start)
	{
		ft_putstr_fd(start->word, 1);
		if (start->next)
			write (1, " ", 1);
		start = start->next;
	}
	if (flag != 2)
		write (1, "\n", 1);
}

// int	main(void)
// {
// 	// Criando nós para testar a função echo
// 	t_word_desc *word1 = malloc(sizeof(t_word_desc));
// 	t_word_desc *word2 = malloc(sizeof(t_word_desc));
// 	t_word_desc *word3 = malloc(sizeof(t_word_desc));

// 	word1->word = "echo";
// 	word1->flags = 0;
// 	word1->next = word2;

// 	word2->word = "-n";  // Simulando uma flag
// 	word2->flags = 2;
// 	word2->next = word3;

// 	word3->word = "Hello, World!";
// 	word3->flags = 0;
// 	word3->next = NULL;

// 	t_world_list input;
// 	input.word = word1;
// 	input.next = NULL;

// 	// Chamando a função echo
// 	echo(&input);

// 	// Liberando memória
// 	free(word1);
// 	free(word2);
// 	free(word3);

// 	return (0);
// }