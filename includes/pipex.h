/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:43:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 14:51:53 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**redir_in;
	char			**redir_out;
	char			**args;
	char			**envp;
}					t_cmd;

void	free_array(char **array);
void	free_cmds(t_cmd *cmds);
char	*append_path(char *cmd, char **env);
int		**mass_pipe(int n);
int		fork_twice(t_cmd *cmds, int** pipefd);
int		child1_exec(t_cmd *cmd, int **pipefd);
int		child2_exec(t_cmd *cmd, int **pipefd);

#endif