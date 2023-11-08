/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:18:06 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 14:32:58 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	*try_pipe(void)
{
	int	*pipefd;

	pipefd = malloc(sizeof(int) * 2);
	if (!pipefd)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (pipe(pipefd) == -1)
	{
		free(pipefd);
		return (NULL);
	}
	return (pipefd);
}

int	**abort_mass_pipe(int **pipes, int i)
{
	while (--i >= 0)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
	return (NULL);
}
int	**mass_pipe(int n)
{
	int	**pipes;
	int	*pipefd;
	int	i;

	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		pipefd = try_pipe();
		if (!pipefd)
			return (abort_mass_pipe(pipes, i));
		pipes[i] = pipefd;
		i++;
	}
	return (pipes);
}
