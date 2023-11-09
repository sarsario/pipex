/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:47 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 21:29:34 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
