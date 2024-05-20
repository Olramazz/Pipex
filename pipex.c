/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olramazz <olramazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:17:42 by olramazz          #+#    #+#             */
/*   Updated: 2024/05/14 12:17:42 by olramazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex *pipex;
	if (ft_check_args(argc) != 0)
		return (1);

	pipex = ft_parse_args(argv);
	if (!pipex)
		return (1);
	ft_exec(pipex, envp);
	ft_free_data_struct(pipex);
	return (0);

}

