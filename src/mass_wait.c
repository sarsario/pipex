/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:02:30 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 11:05:39 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	mass_wait(int *pids, int n)
{
	int	i;
	int	res;

	i = 0;
	while (i < n)
	{
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
