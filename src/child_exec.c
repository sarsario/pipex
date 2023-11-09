/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:51:10 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 14:37:31 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	child_perror(char *msg, int **pipes, int i)
{
	perror(msg);
	close(pipes[i - 1][0]);
	close(pipes[i][1]);
	return (1);
}

static int	try_close_unused(int **pipes, int i, int n)
{
	int	j;

	j = 0;
	while (j < n - 1)
	{
		if (j == i - 1)
		{
			if (close(pipes[j][1]) == -1)
				return (0);
		}
		else if (j == i)
		{
			if (close(pipes[j][0]) == -1)
				return (0);
		}
		else
		{
			if (close(pipes[j][0]) == -1)
				return (0);
			if (close(pipes[j][1]) == -1)
				return (0);
		}
		j++;
	}
	return (1);
}

int	child_exec(t_cmd *cmd, int **pipes, int i, int n)
{
	char	*cmd_path;
	int		fd_in;
	int		fd_out;

	dprintf(2, "child_exec: i: %i | n: %i\n", i, n);
	if (i == 0)
		return (child1_exec(cmd, pipes, i, n));
	if (i == n - 1)
		return (child2_exec(cmd, pipes, i, n));
	dprintf(2, "child_exec: child[%d]\n", i);
	if (i < 0 || i > n - 1 || !try_close_unused(pipes, i, n))
		return (1);
	fd_in = dup2(pipes[i - 1][0], STDIN_FILENO);
	fd_out = dup2(pipes[i][1], STDOUT_FILENO);
	if (fd_out == -1 || fd_in == -1)
		return (child_perror("dup2", pipes, i));
	cmd_path = append_path(cmd->args[0], cmd->envp);
	if (!cmd_path)
		return (child_perror("append_path", pipes, i));
	if (execve(cmd_path, cmd->args, cmd->envp) == -1)
	{
		free(cmd_path);
		return (child_perror("execve", pipes, i));
	}
	return (0);
}
