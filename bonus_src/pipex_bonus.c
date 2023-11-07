/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:43:17 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/07 13:48:29 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/pipex_bonus.h"

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
	return (exec_lst(lst));
}
