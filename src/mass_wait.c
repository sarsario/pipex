/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:02:30 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 14:31:40 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	mass_close(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (close(pipes[i][0]) == -1)
			return (0);
		if (close(pipes[i][1]) == -1)
			return (0);
		i++;
	}
	ft_putstr_fd("Main process: pipes closed\n", 2);
	return (1);
}

int	mass_wait(int *pids, int **pipes, int n)
{
	int	i;
	int	res;

	if (!mass_close(pipes, n))
		return (1);
	i = 0;
	while (i < n)
	{
		dprintf(2, "waiting for child[%i]\n", i);
		if (waitpid(pids[i], &res, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
		if (WIFEXITED(res))
			if (WEXITSTATUS(res))
				return (1);
		i++;
	}
	return (0);
}
