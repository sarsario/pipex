/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:14 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 09:26:14 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/pipex_bonus.h"

int	count_cmd(t_lstcmd *lst)
{
	t_lstcmd	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	**prep_pipe(int nb)
{
	int	i;
	int	**pipes;

	pipes = malloc(sizeof(int *) * nb);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}


// if (i == 0)
// {
// 	j = 0;
// 	while (j < nb)
// 	{
// 		close(pipes[j][0]); // close read end of all pipes
// 		if (i != j)
// 			close(pipes[j][1]); // close write end of all pipes except the first one
// 		j++;
// 	}
// }
// else if (i == nb + 1)
// {
// 	j = 0;
// 	while (j < nb)
// 	{
// 		close(pipes[j][1]); // close write end of all pipes
// 		if (i != j + 1)
// 			close(pipes[j][0]); // close read end of all pipes except the last one
// 		j++;
// 	}
// }
// else
// {
// 	j = 0;
// 	while (j < nb)
// 	{
// 		if (i == j - 1)
// 			close(pipes[j][1]); // close write end of the previous pipe
// 		else if (i == j)
// 			close(pipes[j][0]); // close read end of the current pipe
// 		else
// 		{
// 			close(pipes[j][0]); // close read end of all other pipes
// 			close(pipes[j][1]); // close write end of all other pipes
// 		}
// 		j++;
// 	}
// }
void	close_unused(int **pipes, int i, int nb)
{
	int	j;

	j = 0;
	while (j < nb) {
		if ((i == 0 && j != 0) || (i == nb + 1 && j != nb - 1) || \
			(i != 0 && i != nb + 1 && (j == i - 1 || j == i)))
			close(pipes[j][0]);
		if ((i == 0 && j != 0) || (i == nb + 1 && j != nb - 1) || \
			(i != 0 && i != nb + 1 && (j == i || j == i - 1)))
			close(pipes[j][1]);
		j++;
	}
}

int	child_exec(t_lstcmd *lst, int **pipes, int i, int nb)
{
	int		fd_in;
	int		fd_out;
	char	*cmd_path;

	close_unused(pipes, i, nb);
	if (i == 0)
		fd_in = open(lst->cmd->redir_in[0], O_RDONLY);
	else
		fd_in = pipes[i - 1][0];
	if (i == nb - 1)
		fd_out = open(lst->cmd->redir_out[0],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = pipes[i][1];
	if (fd_in == -1 || fd_out == -1)
	{
		perror("child_exec");
		return (1);
	}
	if (i == 0)
		dup2(fd_in, 0);
	else
		dup2(pipes[i - 1][0], 0);
	if (i == nb - 1)
		dup2(fd_out, 1);
	else
		dup2(pipes[i][1], 1);
	cmd_path = append_path(lst->cmd->cmd[0], lst->cmd->envp);
	if (!cmd_path)
		return (1);
	if (execve(cmd_path, lst->cmd->cmd, lst->cmd->envp) == -1)
	{
		perror("child_exec");
		return (1);
	}
	return (0);
}

void	close_pipes(int **pipes, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	exec_lst(t_lstcmd *lst)
{
	int	nb_cmd;
	int	**pipes;
	int	*pid;
	int	i;

	nb_cmd = count_cmd(lst);
	pipes = prep_pipe(nb_cmd - 1);
	if (!pipes)
		return (1);
	pid = malloc(sizeof(int) * nb_cmd);
	if (!pid)
		return (2);
	i = 0;
	while (i < nb_cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (3);
		if (pid[i] == 0)
			child_exec(lst, pipes, i, nb_cmd);
		i++;
	}
	close_pipes(pipes, nb_cmd - 1);
	i = 0;
	while (i < nb_cmd)
		waitpid(pid[i++], NULL, 0);
	return (0);
}
