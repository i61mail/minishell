/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:36:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/28 11:27:48 by isrkik           ###   ########.fr       */
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
		&& !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i])
			&& vars->read[*i] != '$')
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

void	isthere_quotes(char *str, int *i, int *var)
{
	int	k = *i;
	while (str[k] && !ft_isspace(str[k]) && !ft_issep(str[k]))
	{
		if (ft_isquotes(str[k]))
			*var = 1;
		k++;
	}
	if (*var == 1)
		return ;
}

int	heredoc_count_dollar(char *line, int *i, char **str_temp, int var)
{
	char	temp[2];
	int		len;
	int		b;

	temp[1] = '\0';
	len = 0;
	b = *i;
	while (line[b] && line[b] == '$')
	{
		b++;
		len++;
	}
	if (len == 1 && line[b] && ft_isquotes(line[b]))
	{
		(*i)++;
		return (0);
	}
	if (len % 2 != 0 && len > 1 && var == 1)
		(*i)++;
	while (line[*i] && line[*i] == '$')
	{
		if (len % 2 == 0 || len % 2 != 0)
		{
			temp[0] = line[*i];
			*str_temp = ft_strjoin(*str_temp, temp);
			if (!*str_temp)
				return (-1);
		}
		(*i)++;
	}
	return (0);
}

int	heredoc_delimiter(t_vars *vars, int *i, t_list **comm)
{
	char	*str_temp;
	t_list	*curr;
	int		var;

	curr = NULL;
	str_temp = NULL;
	var = 0;
	if (even_odd(vars->read) == 0)
		return (ft_error(comm), -1);
	isthere_quotes(vars->read, i, &var);
	while (vars->read[*i] && !ft_isspace(vars->read[*i]) && !ft_issep(vars->read[*i]))
	{
		if (vars->read[*i] && vars->read[*i] == 34)
		{
			heredoc_double(vars, i, &str_temp);
			if (vars->read[*i] == 34)
			{
				(*i)++;
			}
		}
		if (vars->read[*i] && vars->read[*i] == 39)
		{
			(*i)++;
			vars->catsh = *i;
			heredoc_single(vars, i, &str_temp);
			if (vars->read[*i] == 39)
				(*i)++;
		}
		if (vars->read[*i] && vars->read[*i] == '$')
			heredoc_count_dollar(vars->read, i, &str_temp, var);
		if (vars->read[*i] && !ft_issep(vars->read[*i]) && !ft_isquotes(vars->read[*i]))
			heredoc_char(vars, i, &str_temp);
	}
	if (var == 1)
		replace_expand(curr, str_temp, comm, 7);
	else
		replace_expand(curr, str_temp, comm, 8);
	return (0);
}

void	skip_digit_here(t_heredoc *herdoc, int *i, int *check)
{
	if (ft_isdigit(herdoc->here_line[*i]))
	{
		*check = 1;
		(*i)++;
	}
}

char	*ft_check_env_here(t_env **envir, char *comp)
{
	char	*exp;
	t_env	*temp;

	temp = *envir;
	exp = NULL;
	while (comp && temp && temp->key)
	{
		if (ft_strcmp(comp, temp->key) == 0)
		{
			exp = ft_strdup(temp->value);
			return (free(comp), exp);
		}
		temp = temp->next;
	}
	return (free(comp), ft_strdup(""));
}

int	expanding_here(t_heredoc *herdoc, int *i, char **str_temp, t_env **envir)
{
	char	tmp[2];
	char	*comp;

	tmp[1] = '\0';
	comp = NULL;
	while (herdoc->here_line[*i] && (ft_isalpha(herdoc->here_line[*i])
			|| herdoc->here_line[*i] == '_' || ft_isdigit(herdoc->here_line[*i])))
	{
		tmp[0] = herdoc->here_line[*i];
		comp = ft_strjoin(comp, tmp);
		if (!comp)
			return (-1);
		(*i)++;
	}
	// if (herdoc->here_line[*i] == '?')
	// {
	// 	comp = ft_itoa(herdoc->);
	// 	*str_temp = ft_strjoin(*str_temp, comp);
	// 	(*i)++;
	// 	return (0);
	// }
	comp = ft_check_env_here(envir, comp);
	if (!comp)
		return (-1);
	*str_temp = ft_strjoin(*str_temp, comp);
	return (free(comp), 0);
}

int	append_dollar2_here(t_heredoc *herdoc, int *i, char **temp, t_env **envir)
{
	if (!ft_isdigit(herdoc->here_line[*i]) && !ft_isalpha(herdoc->here_line[*i])
		&& herdoc->here_line[*i] != '_' && herdoc->len > 1)
		*temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
	if (herdoc->len % 2 != 0 && herdoc->len > 1 && !ft_isdigit(herdoc->here_line[*i]) && herdoc->here_line[*i] != '?'
		&& !ft_isalpha(herdoc->here_line[*i]) && herdoc->here_line[*i] != '_')
		*temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
	else
		*temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len - 1);
	expanding_here(herdoc, i, temp, envir);
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
	free(str);
	return (0);
}


int	here_dollar(t_heredoc *herdoc, int *i, t_env **envir, char **str_temp)
{
	char	*temp;
	int		check;

	check = 0;
	temp = NULL;
	herdoc->start = *i;
	herdoc->len  = count_dollar(herdoc->here_line, i);
	if (herdoc->len % 2 != 0)
	{
		skip_digit_here(herdoc, i, &check);
	}
	if (herdoc->len % 2 != 0 && check == 0)
	{
		append_dollar2_here(herdoc, i, &temp, envir);
	}
	else if (herdoc->len % 2 != 0 && check == 1)
		temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len - 1);
	else
	{
		temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
	}
	*str_temp = ft_strjoin(*str_temp, temp);
	just_alpha_here(herdoc, i, str_temp);
	return (0);
}

int	all_of_it(char **str_temp, int *i, char *here_line)
{
	char	temp[2];

	temp[1] = '\0';
	while (here_line[*i] && here_line[*i])
	{
		temp[0] = here_line[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

char	*expand_heredoc(t_heredoc *herdoc, t_env **envir, int delimiter)
{
	int		i;
	char	temp[2];
	char	*str_temp;
	char *expand = NULL;

	str_temp = NULL;
	temp[1] = '\0';
	i = 0;
	while (herdoc->here_line[i])
	{
		if (delimiter == 7)
		{
			all_of_it(&str_temp, &i, herdoc->here_line);
		}
		else if (herdoc->here_line[i] == '$')
		{
			here_dollar(herdoc, &i, envir, &str_temp);
		}
		else
		{
			while (herdoc->here_line[i] && herdoc->here_line[i] != '$')
			{
				temp[0] = herdoc->here_line[i];
				expand = ft_strjoin(expand, temp);
				if (!expand)
					return (NULL);
				i++;
			}
		}
	}
	expand = ft_strjoin(expand, str_temp);
	return (expand);
}

int	store_here(t_heredoc *herdoc, int fd, t_list *temp, t_env **envir)
{
	char	*value;

	value = NULL;
	if (herdoc->here_line)
	{
		if (ft_strcmp(herdoc->here_line, temp->next->content) == 0)
		{
			exit(0);
		}
		value = expand_heredoc(herdoc, envir, temp->next->type);
		if (!value)
			value = ft_strdup("\0");
		ft_putstr_fd(value , fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

int	read_devrandom(int fd, char **file_name)
{
	int		i;
	char	*str;
	char	_temp[2];

	i = 0;
	_temp[1] = '\0';
	str = malloc(sizeof(char) * 101);
	if (!str)
		return (-1);
	str[100] = '\0';
	if (read(fd, str, 100) == -1)
	{
		return (-1);
	}
	while (i < 40)
	{
		if (ft_isprint(str[i]) && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		{
			_temp[0] = str[i];
			*file_name = ft_strjoin(*file_name, _temp);
			if (!*file_name)
				return (-1);
		}
		i++;
	}
	*file_name = ft_strjoin(*file_name, ".txt");
	if (!*file_name)
		return (-1);
	return (0);
}

int	process_heredoc(t_list *temp, t_vars *vars, t_env **envir)
{
	t_heredoc	herdoc;
	pid_t	return_fork;
	int		child_status = 0;
	char	*file_name = NULL;

	herdoc.expand = NULL;
	herdoc.here_line = NULL;
	herdoc.value = NULL;
	return_fork = 0;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			herdoc.fd = open("/dev/random", O_RDONLY);
			if (herdoc.fd < 0)
				return (-1);
			read_devrandom(herdoc.fd, &file_name);
			close(herdoc.fd);
			herdoc.fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			herdoc.fd1 = open(file_name, O_RDWR | O_TRUNC, 0644);
			unlink(file_name);
			if (herdoc.fd < 0)
				return (-1);
			return_fork = fork();
			if (return_fork < 0)
				return (-1);
			if (return_fork == 0)
			{
				while (1)
				{
					herdoc.here_line = readline("> ");
					if (!herdoc.here_line)
					{
						free(herdoc.here_line);
						break ;
					}
					store_here(&herdoc, herdoc.fd, temp, envir);
				}
				exit(0);
			}
			else
			{
				wait(&child_status);
				if (WIFEXITED(child_status))
					vars->exit_status = WEXITSTATUS(child_status);
			}
			close(herdoc.fd);
			vars->heredoc_fd = herdoc.fd1;
		}
		temp = temp->next;
	}
	return (0);
}

