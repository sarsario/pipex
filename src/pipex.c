/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:36:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/07 12:37:18 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmd	*build_cmd(char **argv, char **envp)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
	{
		errno = ENOMEM;
		return (NULL);
	}
	cmds->next = malloc(sizeof(t_cmd));
	if (!cmds->next)
	{
		free(cmds);
		errno = ENOMEM;
		return (NULL);
	}
	cmds->redir_in = ft_split(argv[1], ' ');
	cmds->redir_out = NULL;
	cmds->args = ft_split(argv[2], ' ');
	cmds->envp = envp;
	cmds->next->redir_in = NULL;
	cmds->next->redir_out = ft_split(argv[4], ' ');
	cmds->next->args = ft_split(argv[3], ' ');
	cmds->next->envp = envp;
	return (cmds);
}

int	child1_exec(t_cmd *cmd, int pipefd[2])
{
	char	*cmd_path;
	int		fd_in;

	close(pipefd[0]);
	fd_in = open(cmd->redir_in[0], O_RDONLY);
	if (fd_in == -1)
	{
		perror("open");
		close(pipefd[1]);
		return (1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
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

int	child2_exec(t_cmd *cmd, int pipefd[2])
{
	char	*cmd_path;
	int		fd_out;

	close(pipefd[1]);
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
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
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

int	fork_twice(t_cmd *cmds, int pipefd[2])
{
	int	pid1;
	int	pid2;
	int	status;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid1 == 0)
	{
		status = child1_exec(cmds, pipefd);
		if (status)
			return (status);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid2 == 0)
	{
		status = child2_exec(cmds->next, pipefd);
		if (status)
			return (status);
	}
	if (close(pipefd[0]) == -1)
	{
		perror("close");
		return (1);
	}
	if (close(pipefd[1]) == -1)
	{
		perror("close");
		return (1);
	}
	if (waitpid(pid1, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (waitpid(pid2, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		pipefd[2];
	int		status;

	if (argc != 5)
	{
		errno = EINVAL;
		perror("argc");
		return (1);
	}
	cmds = build_cmd(argv, envp);
	if (!cmds)
	{
		perror("build_cmd");
		return (1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free_cmds(cmds);
		return (1);
	}
	status = fork_twice(cmds, pipefd);
	if (status)
	{
		free_cmds(cmds);
		return (status);
	}
	free_cmds(cmds);
	return (0);
}
