/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:36:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 21:31:23 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	main_perror(char *msg)
{
	perror(msg);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		**pipes;
	int		status;

	if (argc < 5)
	{
		errno = EINVAL;
		return (main_perror("main"));
	}
	cmds = build_cmd(argc, argv, envp);
	if (!cmds)
		return (main_perror("main"));
	pipes = mass_pipe(argc - 4);
	if (!pipes)
	{
		free_cmds(cmds);
		return (main_perror("pipe"));
	}
	status = mass_fork(cmds, pipes, argc - 3);
	free_cmds(cmds);
	return (status);
}
