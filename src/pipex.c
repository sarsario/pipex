/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:36:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 14:51:30 by osarsari         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		**pipes;
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
	pipes = mass_pipe(2);
	if (!pipes)
	{
		perror("pipe");
		free_cmds(cmds);
		return (1);
	}
	status = fork_twice(cmds, pipes);
	free_cmds(cmds);
	return (status);
}
