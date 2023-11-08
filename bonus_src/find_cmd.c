/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:57:47 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/08 09:35:23 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/pipex_bonus.h"

char	*join_path(char *name, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin(path, "/");
	if (!tmp2)
	{
		errno = ENOMEM;
		return (NULL);
	}
	tmp = tmp2;
	tmp2 = ft_strjoin(tmp2, name);
	free(tmp);
	if (!tmp2)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (tmp2);
}

char	*file_path(char *cmd, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = join_path(cmd, paths[i]);
		if (!tmp)
			return (NULL);
		if (!access(tmp, F_OK))
		{
			if (access(tmp, X_OK) == -1)
			{
				free_array(paths);
				free(tmp);
				return (NULL);
			}
			free_array(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*append_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
			{
				errno = ENOMEM;
				return (NULL);
			}
			cmd_path = file_path(cmd, paths);
			if (!cmd_path)
			{
				errno = ENOENT;
				return (NULL);
			}
			return (cmd_path);
		}
	}
	return (NULL);
}
