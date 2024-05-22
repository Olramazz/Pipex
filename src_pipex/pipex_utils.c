/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:41:50 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/22 15:42:24 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		perror("Invalid number of arguments");
		exit(EXIT_FAILURE);
	}
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		perror("Invalid command");
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK) != 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1)
	{
		perror("Input file does not exist");
		exit(EXIT_FAILURE);
	}
	return (0);
}

t_pipex	*ft_parse_args(char **argv)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd < 0)
	{
		free(pipex);
		ft_error("Error opening input file", NULL);
		exit(EXIT_FAILURE);
	}
	pipex->out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd < 0)
	{
		close(pipex->in_fd);
		free(pipex);
		exit(EXIT_FAILURE);
	}
	pipex->cmd_child = ft_split(argv[2], ' ');
	pipex->cmd_parent = ft_split(argv[3], ' ');
	if (!pipex->cmd_child || !pipex->cmd_parent)
		ft_error("Error parsing commands", pipex);
	return (pipex);
}

char	*get_path(char *cmd, char **envp, t_pipex *pipex)
{
	int		i;
	char	**paths;
	char	*path;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		ft_error("No PATH variable found", pipex);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		ft_error("Error splitting PATH", pipex);
	i = 0;
	while (paths[i])
	{
		path = join_and_check(paths[i], cmd);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*join_and_check(char *path, char *cmd)
{
	char	*full_path;
	int		len;

	len = strlen(path) + strlen(cmd) + 2;
	full_path = (char *)malloc(len);
	if (!full_path)
		return (NULL);
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	return (full_path);
}
