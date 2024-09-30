/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:57 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/30 19:36:32 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_dollar(t_heredoc *herdoc, int *i, t_env **envir, char **str_temp)
{
	char	*temp;
	int		check;

	check = 0;
	temp = NULL;
	herdoc->start = *i;
	herdoc->len = count_dollar(herdoc->here_line, i);
	if (herdoc->len % 2 != 0)
		skip_digit_here(herdoc, i, &check);
	if (herdoc->len % 2 != 0 && check == 0)
	{
		if (append_dollar2_here(herdoc, i, &temp, envir) == -1)
			return (-1);
	}
	else if (herdoc->len % 2 != 0 && check == 1)
		temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len - 1);
	else
		temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
	*str_temp = ft_strjoin(*str_temp, temp);
	free(temp);
	return (0);
}

int	all_of_it(char **str_temp, int *i, char *here_line)
{
	char	temp[2];

	temp[1] = '\0';
	while (here_line[*i])
	{
		temp[0] = here_line[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	alpha_heredoc(char *here_line, int *i, char **expand)
{
	char	temp[2];

	temp[1] = '\0';
	while (here_line[*i] && here_line[*i] != '$')
	{
		temp[0] = here_line[*i];
		*expand = ft_strjoin(*expand, temp);
		if (!*expand)
			return (-1);
		(*i)++;
	}
	return (0);
}

char	*expand_heredoc(t_heredoc *herdoc, t_env **envir, int delimiter)
{
	int		i;
	char	*str_temp;
	char	*expand;

	expand = NULL;
	str_temp = NULL;
	i = 0;
	while (herdoc->here_line[i])
	{
		if (delimiter == HEREDOC_DEL_Q)
		{
			if (all_of_it(&str_temp, &i, herdoc->here_line) == -1)
				return (NULL);
		}
		else if (herdoc->here_line[i] == '$')
		{
			if (here_dollar(herdoc, &i, envir, &str_temp) == -1)
				return (NULL);
		}
		else
			alpha_heredoc(herdoc->here_line, &i, &str_temp);
	}
	expand = ft_strjoin(expand, str_temp);
	return (free(str_temp), expand);
}

int	store_here(t_heredoc *herdoc, t_env **envir, t_vars *vars)
{
	char	*value;

	value = NULL;
	if (herdoc->here_line)
	{
		if (!vars->token)
		{
			vars->token = ft_strdup("\0");
		}
		if (ft_strcmp(herdoc->here_line, vars->token) == 0)
			exit(0);
		value = expand_heredoc(herdoc, envir, vars->del_type);
		if (!value)
			value = ft_strdup("\0");
		ft_putstr_fd(value, herdoc->fd);
		ft_putchar_fd('\n', herdoc->fd);
		free(value);
	}
	return (0);
}
