/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:32:14 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/20 13:32:14 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void ft_exec(t_pipex *pipex, char **envp)
{
	int fd[2];
	pid_t child_pid;
	pid_t parent_pid;
	char *child_path = get_path(pipex->cmd_child[0], envp);
	char *parent_path = get_path(pipex->cmd_parent[0], envp);
	if (pipe(fd) == -1)
	ft_error("could not create pipe", pipex);
	child_pid = fork();
	if (child_pid == -1)
	ft_error("could not fork", pipex);
	if (child_pid == 0)
		child_process(fd, child_path, pipex, envp);
	parent_pid = fork();
	if (parent_pid == -1)
		ft_error("could not fork", pipex);
	if (parent_pid == 0)
	{
		waitpid(child_pid, NULL, 0);
		parent_process(fd, parent_path, pipex, envp);
	}
}

void	child_process(int *fd, char **path, t_pipex *pipex, char **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(pipex->in_fd, STDIN_FILENO);
	close(fd[1]);
	execve(path[0], path, env);
}

void	parent_process(int *fd, char **path, t_pipex *pipex, char **env)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(fd[0]);
	execve(path[0], path, env);
}
