/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:36:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 10:38:38 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		**pipes;
	int		status;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("argc");
		return (1);
	}
	cmds = build_cmd(argc, argv, envp);
	if (!cmds)
	{
		perror("build_cmd");
		return (1);
	}
	pipes = mass_pipe(argc - 4);
	if (!pipes)
	{
		perror("pipe");
		free_cmds(cmds);
		return (1);
	}
	status = mass_fork(cmds, pipes, argc - 3);
	free_cmds(cmds);
	return (status);
}
