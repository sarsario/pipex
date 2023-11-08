/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:30:39 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 09:53:41 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_array(tmp->redir_in);
		free_array(tmp->redir_out);
		free_array(tmp->args);
		free(tmp);
	}
}

void	free_lst(t_lstcmd *lst)
{
	t_lstcmd	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_cmds(tmp->cmd);
		free(tmp);
	}
}
