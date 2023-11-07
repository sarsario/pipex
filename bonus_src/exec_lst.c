/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:14 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/07 15:08:23 by osarsari         ###   ########.fr       */
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

void	close_unused(int **pipes, int i, int nb)
{
	int	j;

	if (i == 0)
	{
		j = 0;
		while (j < nb)
		{
			close(pipes[j][0]); // close read end of all pipes
			if (i != j)
				close(pipes[j][1]); // close write end of all pipes except the first one
			j++;
		}
	}
	else if (i == nb + 1)
	{
		j = 0;
		while (j < nb)
		{
			close(pipes[j][1]); // close write end of all pipes
			if (i != j + 1)
				close(pipes[j][0]); // close read end of all pipes except the last one
			j++;
		}
	}
	else
	{
		j = 0;
		while (j < nb)
		{
			if (i == j - 1)
				close(pipes[j][1]); // close write end of the previous pipe
			else if (i == j)
				close(pipes[j][0]); // close read end of the current pipe
			else
			{
				close(pipes[j][0]); // close read end of all other pipes
				close(pipes[j][1]); // close write end of all other pipes
			}
			j++;
		}
	}
}

int	child_exec(t_lstcmd *lst, int **pipes, int i, int nb)
{
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
