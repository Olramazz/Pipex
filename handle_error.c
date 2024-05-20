/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:48:54 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/20 13:48:54 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_data_struct(t_pipex *pipex)
{
	if (pipex->in_fd > 0)
		close(pipex->in_fd);
	if (pipex->out_fd > 0)
		close(pipex->out_fd);
	if (pipex->cmd_child)
	{
		ft_free_split(pipex->cmd_child);
	}
	if (pipex->cmd_parent)
	{
		ft_free_split(pipex->cmd_parent);
	}
	if (pipex->cmd_paths)
	{
		ft_free_split(pipex->cmd_paths);
	}
	free(pipex);
}

void	ft_error(char *msg, t_pipex *pipex)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (pipex)
		ft_free_data_struct(pipex);
	exit (1);
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
