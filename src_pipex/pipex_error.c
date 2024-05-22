/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:52:49 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/22 14:30:45 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *msg, t_pipex *pipex)
{
	perror(msg);
	ft_free_data_struct(pipex);
	exit(EXIT_FAILURE);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		ft_error("Error in freeing split", NULL);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_data_struct(t_pipex *pipex)
{
	if (pipex->in_fd >= 0)
		close(pipex->in_fd);
	if (pipex->out_fd >= 0)
		close(pipex->out_fd);
	ft_free_split(pipex->cmd_child);
	ft_free_split(pipex->cmd_parent);
	free(pipex);
}
