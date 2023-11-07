/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:03:48 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/07 13:47:18 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/pipex_bonus.h"

t_lstcmd	*first_cmd(int argc, char **argv, char **envp)
{
	t_lstcmd	*lst;
	t_cmd		*cmd;

	lst = malloc(sizeof(t_lstcmd));
	cmd = malloc(sizeof(t_cmd));
	cmd->redir_in = ft_split(argv[1], ' ');
	cmd->cmd = ft_split(argv[2], ' ');
	cmd->redir_out = NULL;
	cmd->envp = envp;
	lst->cmd = cmd;
	lst->next = NULL;
	return (lst);
}

void	add_back(t_lstcmd **lst, char *cmd, char **envp)
{
	t_lstcmd	*new;
	t_cmd		*new_cmd;
	t_lstcmd	*tmp;

	new = malloc(sizeof(t_lstcmd));
	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->redir_in = NULL;
	new_cmd->cmd = ft_split(cmd, ' ');
	new_cmd->redir_out = NULL;
	new_cmd->envp = envp;
	new->cmd = new_cmd;
	new->next = NULL;
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_last(t_lstcmd **lst, char **argv, char **envp, int i)
{
	t_lstcmd	*new;
	t_cmd		*new_cmd;
	t_lstcmd	*tmp;

	new = malloc(sizeof(t_lstcmd));
	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->redir_in = NULL;
	new_cmd->cmd = ft_split(argv[i], ' ');
	new_cmd->redir_out = ft_split(argv[i + 1], ' ');
	new_cmd->envp = envp;
	new->cmd = new_cmd;
	new->next = NULL;
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// infile	cmd1	cmd2	cmd3	cmd4	cmd5	outfile
// argv[1]	argv[2]	argv[3]	argv[4]	argv[5]	argv[6]	argv[7] argc = 8

t_lstcmd	*parse_args(int argc, char **argv, char **envp)
{
	t_lstcmd	*lst;
	int			i;

	lst = first_cmd(argc, argv, envp);
	i = 3;
	while (i < argc - 3)
		add_back(&lst, argv[i++], envp);
	add_last(&lst, argv, envp, i);
	return (lst);
}