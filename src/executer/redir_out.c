/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:11:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/15 13:34:22 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execute.h"
#include "../../include/utils.h"

static int	redir_count(t_word *word, int *type);
static void	alloc_fd(int **fd, int count);
static char	**get_file_array(t_word *word, int count);
static void	create_files(int *fd, char **files, int count, int type);

void	redir_out(t_word *word)
{
	int	count;
	int type;
	int	*fd;
	char **files;

	type = 0;
	ft_bzero(&files, sizeof(char *));
	count = redir_count(word, &type);
	if (!count)
		return ;
	alloc_fd(&fd, count);
	files = get_file_array(word, count);
	create_files(fd, files, count, type);
    close_fd(fd, count);
	free_strarray(files);
}

static int	redir_count(t_word *word, int *type)
{
	t_word	*tmp;
	int		count;

	tmp = word;
	count = 0;
	while (tmp)
	{
		if (tmp->redir == OUT)
		{
			*type = 1;
			count++;
		}
		else if (tmp->redir == APPEND)
		{
			*type = 2;
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

static void	alloc_fd(int **fd, int count)
{
	*fd = ft_calloc(count, sizeof(int));
	if (!fd)
		perror("minishell: ft_calloc");
}

static char	**get_file_array(t_word *word, int count)
{
	t_word	*tmp;
	int		i;
	char 	**files;

	tmp = word;
	i = 0;
	files = ft_calloc(count + 1, sizeof(char *));
	if (!files)
	{
		perror("minishell: ft_calloc");
		return (NULL);
	}
	while (tmp)
	{
		if (tmp->redir == OUT || tmp->redir == APPEND)
		{
			tmp = tmp->next;
			files[i] = ft_strdup(tmp->word);
			i++;
		}
		tmp = tmp->next;
	}
	files[count] = 0;
	return (files);
}

static void	create_files(int *fd, char **files, int count, int type)
{
	int	i;

	(void)type;
	i = 0;
	while (i < count)
	{
		if (type == 1)
			fd[i] = open(files[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (type == 2)
			fd[i] = open(files[i], O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
		if (fd[i] == -1)
		{
			print_fd(STDERR_FILENO, "minishell: %s: ", files[i]);
			perror("");
			return ;
		}
		i++;
	}
	redirect_stdout(fd, i - 1);
}
