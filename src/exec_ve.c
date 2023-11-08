/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:51:10 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 14:51:37 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	child1_exec(t_cmd *cmd, int **pipefd)
{
	char	*cmd_path;
	int		fd_in;

	close(pipefd[0][0]);
	fd_in = open(cmd->redir_in[0], O_RDONLY);
	if (fd_in == -1)
	{
		perror("open");
		close(pipefd[0][1]);
		return (1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	if (dup2(pipefd[0][1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	cmd_path = append_path(cmd->args[0], cmd->envp);
	if (!cmd_path)
	{
		perror("append_path");
		return (1);
	}
	if (execve(cmd_path, cmd->args, cmd->envp) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}

int	child2_exec(t_cmd *cmd, int **pipefd)
{
	char	*cmd_path;
	int		fd_out;

	close(pipefd[0][1]);
	fd_out = open(cmd->redir_out[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	if (dup2(pipefd[0][0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	cmd_path = append_path(cmd->args[0], cmd->envp);
	if (!cmd_path)
	{
		perror("append_path");
		return (1);
	}
	if (execve(cmd_path, cmd->args, cmd->envp) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}
