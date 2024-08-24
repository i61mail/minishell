/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:36:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/24 17:40:55 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_single(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[*i] == 39)
		(*i)++;
	while (vars->read[*i] && vars->read[*i] != 39)
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	heredoc_double(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[*i] == 34)
		(*i)++;
	while (vars->read[*i] && vars->read[*i] != 34)
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	heredoc_char(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && !ft_issep(vars->read[*i])
		&& !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i]))
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	heredoc_delimiter(t_vars *vars, int *i, t_list **comm)
{
	char	*str_temp;
	t_list	*curr;

	curr = NULL;
	str_temp = NULL;
	if (even_odd(vars->read) == 0)
		return (ft_error(comm), -1);
	while (vars->read[*i] && !ft_isspace(vars->read[*i]) && !ft_issep(vars->read[*i]))
	{
		if (vars->read[*i] == 34)
		{
			heredoc_double(vars, i, &str_temp);
			if (vars->read[*i] == 34)
				(*i)++;
		}
		if (vars->read[*i] == 39)
		{
			(*i)++;
			vars->catsh = *i;
			heredoc_single(vars, i, &str_temp);
			if (vars->read[*i] == 39)
				(*i)++;
		}
		if (!ft_issep(vars->read[*i]) && !ft_isquotes(vars->read[*i]))
			heredoc_char(vars, i, &str_temp);
	}
	replace_expand(curr, str_temp, comm, 7);
	process_heredoc(*comm, vars);
	return (0);
}

int	store_here(char *here_line, int fd, char *next)
{
    (void)next;
	if (here_line)
	{
		ft_putstr_fd(here_line ,fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

int	process_heredoc(t_list *temp, t_vars *vars)
{
	char	*here_line;
	int		fd;
	pid_t	return_fork;
	int		child_status = 0;

	return_fork = 0;
	fd = 0;
	(void)vars;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			return_fork = fork();
			if (return_fork < 0)
				return (-1);
			if (return_fork == 0)
			{
				fd = open("file.txt", O_CREAT | O_RDWR, 0777);
				if (fd < 0)
					return (-1);
				while (1)
				{
					here_line = readline("> ");
					if (!here_line)
					{
						break ;
						free(here_line);
					}
					store_here(here_line, fd, temp->next->content);
				}
				close(fd);
				exit(0);
			}
			else
				wait(&child_status);
		}
		temp = temp->next;
	}
	return (0);
}

