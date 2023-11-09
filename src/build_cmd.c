/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:51:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/09 09:28:34 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmd	*build_head(char **argv, char **envp)
{
	t_cmd	*head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (NULL);
	head->redir_in = ft_split(argv[1], ' ');
	head->args = ft_split(argv[2], ' ');
	if (!head->args || !head->redir_in)
	{
		if (head->args)
			free_array(head->args);
		if (head->redir_in)
			free_array(head->redir_in);
		free(head);
		errno = ENOMEM;
		return (NULL);
	}
	head->redir_out = NULL;
	head->envp = envp;
	head->next = NULL;
	return (head);
}

int	build_between(t_cmd **head, int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		i;

	i = 2;
	next = *head;
	while (++i < argc - 3)
	{
		next = next->next;
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (0);
		cmd->redir_in = NULL;
		cmd->args = ft_split(argv[i], ' ');
		if (!cmd->args)
		{
			free(cmd);
			return (0);
		}
		cmd->redir_out = NULL;
		cmd->envp = envp;
		cmd->next = NULL;
		next = cmd;
	}
	return (1);
}

int	build_tail(t_cmd **head, int argc, char **argv, char **envp)
{
	t_cmd	*tail;

	tail = malloc(sizeof(t_cmd));
	if (!tail)
		return (0);
	tail->redir_in = NULL;
	tail->args = ft_split(argv[argc - 2], ' ');
	tail->redir_out = ft_split(argv[argc - 1], ' ');
	if (!tail->args || !tail->redir_out)
	{
		if (tail->args)
			free_array(tail->args);
		if (tail->redir_out)
			free_array(tail->redir_out);
		free(tail);
		errno = ENOMEM;
		return (0);
	}
	tail->envp = envp;
	tail->next = NULL;
	(*head)->next = tail;
	return (1);
}

t_cmd	*build_cmd(int argc, char **argv, char **envp)
{
	t_cmd	*head;

	head = build_head(argv, envp);
	if (!head)
		return (NULL);
	if (!build_between(&head, argc, argv, envp))
	{
		free_cmds(head);
		errno = ENOMEM;
		return (NULL);
	}
	if (!build_tail(&head, argc, argv, envp))
	{
		free_cmds(head);
		return (NULL);
	}
	return (head);
}
