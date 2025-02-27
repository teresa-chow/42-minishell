/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu  <carlaugu@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/02/27 14:45:01 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include <stdlib.h>

# include "../lib/libft/libft/libft.h"

char	*get_path(char **envp);

#endif