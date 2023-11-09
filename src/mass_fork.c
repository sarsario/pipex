/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:47 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 12:02:00 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// int	fork_twice(t_cmd *cmds, int** pipefd)
// {
// 	int	*pids;
// 	int	status;

// 	pids = malloc(sizeof(int) * 2);
// 	if (!pids)
// 	{
// 		perror("malloc");
// 		return (1);
// 	}
// 	pids[0] = fork();
// 	if (pids[0] == -1)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	if (pids[0] == 0)
// 	{
// 		status = child1_exec(cmds, pipefd);
// 		if (status)
// 			return (status);
// 	}
// 	pids[1] = fork();
// 	if (pids[1] == -1)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	if (pids[1] == 0)
// 	{
// 		status = child2_exec(cmds->next, pipefd);
// 		if (status)
// 			return (status);
// 	}
// 	if (close(pipefd[0][0]) == -1)
// 	{
// 		perror("close");
// 		return (1);
// 	}
// 	if (close(pipefd[0][1]) == -1)
// 	{
// 		perror("close");
// 		return (1);
// 	}
// 	if (waitpid(pids[0], &status, 0) == -1)
// 	{
// 		perror("waitpid");
// 		return (1);
// 	}
// 	if (waitpid(pids[1], &status, 0) == -1)
// 	{
// 		perror("waitpid");
// 		return (1);
// 	}
// 	free(pids);
// 	return (status);
// }

int	mass_fork(t_cmd *head, int **pipes, int n)
{
	int	*pids;
	int	status;
	int	i;

	pids = malloc(sizeof(int) * n);
	if (!pids)
		return (1);
	i = 0;
	while (head)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			free(pids);
			return (1);
		}
		if (pids[i] == 0)
			return (child_exec(head, pipes, i, n));
		i++;
		head = head->next;
	}
	status = mass_wait(pids, pipes, n);
	free(pids);
	return (status);
}
