/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:36:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/26 14:00:25 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_str_temp(t_vars *vars, int *i, char **str_temp, int check)
{
	if (check == 1)
	{
		(*i)++;
		vars->catsh = *i;
		heredoc_single(vars, i, str_temp);
		if (vars->read[*i] == 39)
			(*i)++;
	}
	else
	{
		heredoc_double(vars, i, str_temp);
		if (vars->read[*i] == 34)
			(*i)++;
	}
}

static void	init_heredoc(t_heredoc *herdoc)
{
	herdoc->expand = NULL;
	herdoc->here_line = NULL;
	herdoc->value = NULL;
	herdoc->return_fork = 0;
	herdoc->fd = 0;
	herdoc->passed_fd = 0;
	herdoc->file_name = NULL;
	herdoc->child_status = 0;
}

void	child_exitstatus(t_heredoc *herdoc, t_vars *vars)
{
	wait(&herdoc->child_status);
	if (WIFEXITED(herdoc->child_status))
		vars->exit_status = WEXITSTATUS(herdoc->child_status);
	else if (WIFSIGNALED(herdoc->child_status))
		vars->exit_status = 128 + WTERMSIG(herdoc->child_status);
	ft_catch(0, -1);
	tcsetattr(0, 0, &vars->reset);
}

void	read_heredoc(t_heredoc *herdoc, t_env **envir, t_vars *vars)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		herdoc->here_line = readline("> ");
		if (!herdoc->here_line)
		{
			free(herdoc->here_line);
			break ;
		}
		store_here(herdoc, envir, vars);
		free(herdoc->here_line);
	}
	exit(0);
}

int	process_heredoc(t_vars *vars, t_env **envir)
{
	t_heredoc	herdoc;

	init_heredoc(&herdoc);
	if (gen_file_name(&herdoc) == -1)
		return (-1);
	herdoc.parrent_status = vars->exit_status;
	herdoc.return_fork = fork();
	if (herdoc.return_fork < 0)
		return (-1);
	ft_catch(0, 2);
	if (herdoc.return_fork == 0)
		read_heredoc(&herdoc, envir, vars);
	else
		child_exitstatus(&herdoc, vars);
	tcsetattr(0, 0, &vars->reset);
	close(herdoc.fd);
	vars->heredoc_fd = herdoc.passed_fd;
	free(vars->token);
	return (0);
}
