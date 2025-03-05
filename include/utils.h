/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/27 12:09:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include <stdlib.h>

typedef struct s_env_node
{
	char	*var;
	struct s_env_node *next;
}	t_env_node;


int	ft_strcmp(const char *s1, const char *s2); // put in libft??
int	init_env_lst(char **envp, t_env_node **env_lst);
void	free_strarray(char **array);
void	free_env_list(t_env_node *lst);

#endif