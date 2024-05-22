/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:12:23 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/22 12:54:46 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	**cmd_paths;
	char	**cmd_child;
	char	**cmd_parent;
}	t_pipex;

int			ft_check_args(int argc, char **argv);
t_pipex		*ft_parse_args(char **argv);
void		ft_exec(t_pipex *pipex, char **envp);
void		ft_free_data_struct(t_pipex *pipex);
void		ft_error(char *msg, t_pipex *pipex);
void		child_process(int *fd, char *path, t_pipex *pipex, char **env);
void		parent_process(int *fd, char *path, t_pipex *pipex, char **env);
void		ft_free_split(char **split);
char		*get_path(char *cmd, char **envp, t_pipex *pipex);
char		*join_and_check(char *path, char *cmd);

#endif
