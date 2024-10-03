/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:36:10 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/28 17:38:20 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_check_env_here(t_env **envir, char *comp, t_heredoc *herdoc)
{
	char	*exp;
	t_env	*temp;

	temp = *envir;
	exp = NULL;
	if (!comp)
		return (NULL);
	while (comp && temp && temp->key)
	{
		if (ft_strncmp(comp, "_\0", 2) == 0)
		{
			if (herdoc->last_arg)
			{
				exp = ft_strdup(herdoc->last_arg);
				return (free(comp), exp);
			}
		}
		if (ft_strcmp(comp, temp->key) == 0)
		{
			exp = ft_strdup(temp->value);
			return (free(comp), exp);
		}
		temp = temp->next;
	}
	return (free(comp), ft_strdup(""));
}

int	heredoc_status(char *comp, char **str_temp, int *i, t_heredoc *herdoc)
{
	comp = ft_itoa(herdoc->parrent_status);
	*str_temp = ft_strjoin(*str_temp, comp);
	if (comp && comp[0] != '0')
		free(comp);
	(*i)++;
	return (0);
}

int	expanding_here(t_heredoc *herdoc, int *i, char **str_temp, t_env **envir)
{
	char	tmp[2];
	char	*comp;

	tmp[1] = '\0';
	comp = NULL;
	while (herdoc->here_line[*i] && (ft_isalpha(herdoc->here_line[*i])
			|| herdoc->here_line[*i] == '_'
			|| ft_isdigit(herdoc->here_line[*i])))
	{
		tmp[0] = herdoc->here_line[*i];
		comp = ft_strjoin(comp, tmp);
		(*i)++;
	}
	if (herdoc->here_line[*i] == '?')
		return (heredoc_status(comp, str_temp, i, herdoc), 0);
	comp = ft_check_env_here(envir, comp, herdoc);
	if (comp)
		*str_temp = ft_strjoin(*str_temp, comp);
	if (*str_temp[0] == '\0')
	{
		free(*str_temp);
		*str_temp = NULL;
	}
	return (free(comp), 0);
}

int	append_dollar2_here(t_heredoc *herdoc, int *i, char **temp, t_env **envir)
{
	if (!ft_isdigit(herdoc->here_line[*i]) && !ft_isalpha(herdoc->here_line[*i])
		&& herdoc->here_line[*i] != '_' && herdoc->len > 1)
	{
		*temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
		if (!*temp)
			return (-1);
	}
	if (herdoc->len % 2 != 0 && !ft_isdigit(herdoc->here_line[*i])
		&& herdoc->here_line[*i] != '?' && !ft_isalpha(herdoc->here_line[*i])
		&& herdoc->here_line[*i] != '_' && herdoc->len > 1)
	{
		*temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
		if (!*temp)
			return (-1);
	}
	else
	{
		*temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len - 1);
		if (!*temp)
			return (-1);
	}
	if (expanding_here(herdoc, i, temp, envir) == -1)
		return (-1);
	return (0);
}

int	just_alpha_here(t_heredoc *herdoc, int *i, char **str_temp)
{
	char	temp[2];
	char	*str;

	str = NULL;
	temp[1] = '\0';
	while (herdoc->here_line[*i] && herdoc->here_line[*i] != '$')
	{
		temp[0] = herdoc->here_line[*i];
		str = ft_strjoin(str, temp);
		if (!str)
			return (-1);
		(*i)++;
	}
	*str_temp = ft_strjoin(*str_temp, str);
	return (free(str), 0);
}
