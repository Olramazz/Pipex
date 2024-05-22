/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:33:23 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/22 16:01:55 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_pipex *pipex, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*child_cmd_path;
	char	*parent_cmd_path;

	if (pipe(fd) == -1)
		ft_error("Pipe error", pipex);
	pid1 = fork();
	if (pid1 < 0)
		ft_error("Fork error", pipex);
	if (pid1 == 0)
	{
		child_cmd_path = get_path(pipex->cmd_child[0], envp, pipex);
		if (!child_cmd_path)
			ft_error("Command not found", pipex);
		child_process(fd, child_cmd_path, pipex, envp);
	}
	pid2 = fork();
	if (pid2 < 0)
		ft_error("Fork error", pipex);
	if (pid2 == 0)
	{
		parent_cmd_path = get_path(pipex->cmd_parent[0], envp, pipex);
		if (!parent_cmd_path)
			ft_error("Command not found", pipex);
		parent_process(fd, parent_cmd_path, pipex, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	child_process(int *fd, char *path, t_pipex *pipex, char **env)
{
	if (dup2(pipex->in_fd, STDIN_FILENO) < 0)
	{
		perror("Dup2 error");
		exit(1);
	}
	if (dup2(fd[1], STDOUT_FILENO) < 0)
	{
		perror("Dup2 error");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	execve(path, pipex->cmd_child, env);
	perror("Execve error");
	exit(1);
}

void	parent_process(int *fd, char *path, t_pipex *pipex, char **env)
{
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		perror("Dup2 error");
		exit(1);
	}
	if (dup2(pipex->out_fd, STDOUT_FILENO) < 0)
	{
		perror("Dup2 error");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	execve(path, pipex->cmd_parent, env);
	perror("Execve error");
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (ft_check_args(argc, argv))
		exit(EXIT_FAILURE);
	pipex = ft_parse_args(argv);
	if (!pipex)
		return (1);
	ft_exec(pipex, envp);
	ft_free_data_struct(pipex);
	return (0);
}
