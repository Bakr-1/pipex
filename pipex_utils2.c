/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:33 by aalseri           #+#    #+#             */
/*   Updated: 2022/06/23 13:27:14 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*child_pipex(t_pipex *p)
{
	if (p->pid1)
	{
		dup2(p->in_fd, STDIN_FILENO);
		dup2(p->fd[1], STDOUT_FILENO);
		close(p->fd[0]);
		close(p->in_fd);
		printf("in pid1 = %d\n", p->pid1);
		ft_putstr_fd("test\n", 2);
		execve(p->cmd1[0], p->pcmd1, p->envp);
	}
	else
	{
		p->pid2 = fork();
		if (p->pid2)
		{
			dup2(p->out_fd, STDOUT_FILENO);
			dup2(p->fd[0], STDIN_FILENO);
			close(p->fd[1]);
			close(p->out_fd);
			printf("fdin pid2 = %d\n", p->pid2);
			ft_putstr_fd("from child 2\n", 2);
			execve(p->cmd2[0], p->pcmd2, p->envp);
		}
	}
	printf("pid1 = %d\n", p->pid1);
	printf("pid2 = %d\n", p->pid2);
	if (wait(0) == -1)
		printf("Waitpid failed\n");
	wait(0);
		// if(waitpid(p->pid1, NULL, 0) ==  -1)
		// if(waitpid(p->pid2, NULL, 0) ==  -1)
		// 	printf("Waitpid failed\n");
	return (p);
}

t_pipex	*pipex(t_pipex *p)
{
	if (pipe(p->fd) == -1)
		ft_error("pipe", strerror(errno), EXIT_FAILURE, p);
	p->pid1 = fork();
	if (p->pid1 == -1)
		ft_error("fork", strerror(errno), EXIT_FAILURE, p);
	child_pipex(p);
	return (p);
}
