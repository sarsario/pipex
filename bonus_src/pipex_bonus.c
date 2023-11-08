/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:43:17 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 11:50:40 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/pipex_bonus.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_lstcmd	*lst;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("pipex");
		return (1);
	}
	lst = parse_args(argc, argv, envp);
	int res = exec_lst(lst);
	ft_printf("exec_lst returned %d\n", res);
	free_lst(lst);
	return (res);
}
