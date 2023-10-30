/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:36:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 13:36:14 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*build_cmd(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->next = malloc(sizeof(t_cmd));
	if (!cmds.next)
		return (free(cmds), NULL);
	cmds->redir_in = ft_split(argv[2], ' ');
	cmds->redir_out = NULL;
	cmds->args = ft_split(argv[3], ' ');
	cmds->envp = envp;
	cmds->next->redir_in = NULL;
	cmds->next->redir_out = ft_split(argv[4], ' ');
	cmds->next->args = NULL;
	cmds->next->envp = envp;
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;

	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (1);
	}
	cmds = build_cmd(argc, argv, envp);
}
