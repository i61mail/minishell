/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:10:30 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 22:13:01 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_ambiguos(t_list *next_node, t_vars *vars)
{
	(void)next_node;
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(" ambiguous redirect\n", 2);
	vars->exit_status = 1;
}

int	ft_redout(t_list *next_node, t_vars *vars)
{
	int	fd;

	if ((!ft_strcmp(next_node->content, "stdin")
			&& !ft_strcmp(getcwd(NULL, PATH_MAX), "/dev"))
		|| !ft_strcmp(next_node->content, "/dev/stdin"))
	{
		if (vars->numofpipes && vars->cmd_num)
			return (ft_putstr_fd("minishell: /dev/stdin: \
Permission denied\n", 2), -1);
		return (0);
	}
	fd = open(next_node->content, O_CREAT | O_WRONLY | O_TRUNC, 0622);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(next_node->content);
		vars->exit_status = 1;
		return (-1);
	}
	if (vars->pfd[1] != 1)
		close(vars->pfd[1]);
	vars->pfd[1] = fd;
	return (0);
}

int	ft_redappend(t_list *next_node, t_vars *vars)
{
	int	fd;

	fd = open(next_node->content, O_WRONLY | O_CREAT | O_APPEND, 0622);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(next_node->content);
		vars->exit_status = 1;
		return (-1);
	}
	if (vars->pfd[1] != 1)
		close(vars->pfd[1]);
	vars->pfd[1] = fd;
	return (0);
}

int	ft_redin(t_list *next_node, t_vars *vars)
{
	int	fd;

	if ((!ft_strcmp(next_node->content, "stdout")
			&& !ft_strcmp(getcwd(NULL, PATH_MAX), "/dev"))
		|| !ft_strcmp(next_node->content, "/dev/stdout"))
	{
		if (vars->numofpipes && vars->pipe)
			return (ft_putstr_fd("minishell: /dev/stdout: \
Permission denied\n", 2), -1);
		return (0);
	}
	fd = open(next_node->content, O_RDONLY);
	if (fd == -1)
	{
		if (vars->heredoc_fd != 0)
			close(vars->heredoc_fd);
		ft_putstr_fd("minishell: ", 2);
		perror(next_node->content);
		vars->exit_status = 1;
		return (-1);
	}
	if (vars->old_fd != 0 && vars->old_fd != 1)
		close(vars->old_fd);
	vars->old_fd = fd;
	return (0);
}

int	ft_redheredoc(t_list *next_node, t_vars *vars)
{
	if (vars->hdoc)
		return (0);
	if (vars->heredoc_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(next_node->content);
		vars->exit_status = 1;
		return (-1);
	}
	if (vars->old_fd != 0 && vars->old_fd != 1)
		close(vars->old_fd);
	vars->old_fd = vars->heredoc_fd;
	vars->hdoc = 1;
	return (0);
}
