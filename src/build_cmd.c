/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:51:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 22:32:43 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	try_fill_cmd(t_cmd *cmd, char **argv, int i)
{
	if (i == 0)
		cmd->redir_in = ft_split(argv[1], ' ');
}

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
