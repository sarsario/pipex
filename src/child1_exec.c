/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child1_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:16:03 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 21:32:15 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	try_close_unused(int **pipes, int i, int n)
{
	int	j;

	j = 0;
	while (j < n - 1)
	{
		if (j == i)
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

static int	child_perror(char *msg, int **pipes, int i)
{
	perror(msg);
	close(pipes[i][1]);
	return (1);
}

int	child1_exec(t_cmd *cmd, int **pipefd, int i, int n)
{
	char	*cmd_path;
	int		fd_in;

	if (!try_close_unused(pipefd, i, n))
		return (1);
	fd_in = open(cmd->redir_in[0], O_RDONLY);
	if (fd_in == -1)
		return (child_perror("open", pipefd, i));
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (child_perror("dup2", pipefd, i));
	if (dup2(pipefd[i][1], STDOUT_FILENO) == -1)
		return (child_perror("dup2", pipefd, i));
	cmd_path = append_path(cmd->args[0], cmd->envp);
	if (!cmd_path)
		return (child_perror("append_path", pipefd, i));
	if (execve(cmd_path, cmd->args, cmd->envp) == -1)
	{
		free(cmd_path);
		return (child_perror("execve", pipefd, i));
	}
	return (0);
}
