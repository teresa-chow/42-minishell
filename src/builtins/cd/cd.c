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

void	cd(t_word *input)
{
	char	*path;

	if (input->next)
		path = input->next->word;
	// 	//// if there is not word->next, means that we only have cd command,
    //     //so we have to get $HOME path
	printf("we are in %s\n", getcwd(NULL, 0)); // we have to free the return of getcwd but this call is only to test
	if (chdir(path) == 0)
		ft_printf("Now, we are in %s\n", getcwd(NULL, 0));
    else
        ft_printf("Error: %s\n", strerror(errno));
}

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)envp;
//      t_word_desc *desc1 = (t_word_desc *)malloc(sizeof(t_word_desc));
//     t_word_desc *desc2 = (t_word_desc *)malloc(sizeof(t_word_desc));

//     desc1->word = "cd";  // Comando (mas não utilizado diretamente na função cd)
//     desc1->next = desc2;

//     desc2->word = "-";  // Caminho para o qual queremos mudar
//     desc2->next = NULL;

//     // Criando a estrutura t_word_list
//     t_world_list *input = (t_world_list *)malloc(sizeof(t_world_list));
//     input->word = desc1;
//     input->next = NULL;

//     // Chama a função cd
//     cd(input);

//     // Libera a memória alocada
//     free(desc1);
//     free(desc2);
//     free(input);

//     return 0;
// }
