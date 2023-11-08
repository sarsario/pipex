/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:40:54 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 09:53:29 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_cmd
{
	char	**redir_in;
	char	**redir_out;
	char	**cmd;
	char	**envp;
}			t_cmd;

typedef	struct s_lstcmd
{
	t_cmd			*cmd;
	struct s_lstcmd	*next;
}					t_lstcmd;

void		free_array(char **array);
void		free_cmds(t_cmd *cmds);
void		free_lst(t_lstcmd *lst);
t_lstcmd	*parse_args(int argc, char **argv, char **envp);
char		*append_path(char *cmd, char **env);
int			exec_lst(t_lstcmd *lst);

#endif