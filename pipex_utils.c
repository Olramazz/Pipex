/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:28:12 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/14 16:28:12 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_check_args(int argc)
{
	if (argc != 5)
	ft_error("Invalid number of arguments", NULL);
	return (0);
}

t_pipex *ft_parse_args(char **argv)
{
	t_pipex *pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd < 0)
		ft_error("could not open input file", pipex);
	pipex->out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd < 0)
		ft_error("could not open output file", pipex);
	pipex->cmd_child = ft_split(argv[2], ' ');
	if (!pipex->cmd_child)
		ft_error("child cmd not valid", pipex)
	pipex->cmd_parent = ft_split(argv[3], ' ');
	if (!pipex->cmd_parent)
		ft_error("child cmd not valid", pipex)
	return (pipex);
}

void ft_free_split(char **split)
{
	int i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char *get_path(char *cmd, char **envp, t_pipex *pipex)
{
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			char **paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				ft_error("could not split PATH", pipex);
			int j = 0;
			while (paths[j])
			{
				char *path = ft_strjoin(paths[j], "/");
				char *cmd_path = ft_strjoin(path, cmd);
				free(path);
				if (access(cmd_path, X_OK) == 0)
				{
					ft_free_split(paths);
					return (cmd_path);
				}
				free(cmd_path);
				j++;
			}
			ft_free_split(paths);
			ft_error("command not found", pipex);
		}
		i++;
	}
	return (NULL);
}

