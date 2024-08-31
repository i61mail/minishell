/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:36:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/31 23:36:02 by isrkik           ###   ########.fr       */
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
				(*i)++;
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
	{
		vars->del_type = HEREDOC_DEL_Q;
		vars->token = ft_strdup(str_temp);
		replace_expand(curr, str_temp, comm, HEREDOC_DEL_Q);
	}
	else
	{
		vars->del_type = HEREDOC_DEL_U;
		vars->token = ft_strdup(str_temp);
		replace_expand(curr, str_temp, comm, HEREDOC_DEL_U);
	}
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
			if (!exp)
				return (NULL);
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
	if (!*str_temp)
		return (-1);
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
	if (herdoc->len % 2 != 0 && herdoc->len > 1 && !ft_isdigit(herdoc->here_line[*i]) && herdoc->here_line[*i] != '?'
		&& !ft_isalpha(herdoc->here_line[*i]) && herdoc->here_line[*i] != '_')
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
	if (!*str_temp)
		return (free(str), -1);
	return (free(str), 0);
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
		skip_digit_here(herdoc, i, &check);
	if (herdoc->len % 2 != 0 && check == 0)
	{
		if (append_dollar2_here(herdoc, i, &temp, envir) == -1)
			return (-1);
	}
	else if (herdoc->len % 2 != 0 && check == 1)
	{
		temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len - 1);
		if (!temp)
			return (-1);
	}
	else
	{
		temp = ft_substr(herdoc->here_line, herdoc->start, herdoc->len);
		if (!temp)
			return (-1);
	}
	*str_temp = ft_strjoin(*str_temp, temp);
	if (!*str_temp)
		return (-1);
	if (just_alpha_here(herdoc, i, str_temp) == -1)
		return (-1);
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
		{
			if (alpha_heredoc(herdoc->here_line, &i, &expand) == -1)
				return (NULL);
		}
	}
	expand = ft_strjoin(expand, str_temp);
	if (!expand)
		return (NULL);
	return (expand);
}

int	store_here(t_heredoc *herdoc, t_list *temp, t_env **envir, t_vars *vars)
{
	char	*value;

	value = NULL;
	(void)temp;
	if (herdoc->here_line)
	{
		if (ft_strcmp(herdoc->here_line, vars->token) == 0)
			exit(0);
		value = expand_heredoc(herdoc, envir, vars->del_type);
		if (!value)
			value = ft_strdup("\0");
		ft_putstr_fd(value , herdoc->fd);
		ft_putchar_fd('\n', herdoc->fd);
	}
	return (0);
}

int	printable_char(char *str, int *i, char **file_name)
{
	char	temp[2];

	temp[1] = '\0';
	if (ft_isprint(str[*i]) && (ft_isalpha(str[*i]) || ft_isdigit(str[*i])))
	{
		temp[0] = str[*i];
		*file_name = ft_strjoin(*file_name, temp);
		if (!*file_name)
			return (-1);
	}
	return (0);
}

int	read_devrandom(int fd, char **file_name)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * 101);
	if (!str)
		return (-1);
	str[100] = '\0';
	if (read(fd, str, 100) == -1)
		return (-1);
	while (i < 40)
	{
		if (printable_char(str, &i, file_name) == -1)
			return (-1);
		i++;
	}
	*file_name = ft_strjoin(*file_name, ".txt");
	if (!*file_name)
		return (-1);
	return (0);
}

void	init_heredoc(t_heredoc *herdoc)
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

int	gen_file_name(t_heredoc *herdoc)
{
	herdoc->fd = open("/dev/random", O_RDONLY);
	if (herdoc->fd < 0)
		return (-1);
	if (read_devrandom(herdoc->fd, &herdoc->file_name) == -1)
		return (-1);
	close(herdoc->fd);
	herdoc->fd = open(herdoc->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	herdoc->passed_fd = open(herdoc->file_name, O_RDWR | O_TRUNC, 0644);
	unlink(herdoc->file_name);
	if (herdoc->fd < 0 || herdoc->passed_fd < 0)
		return (-1);
	return (0);
}

void	child_exitstatus(t_heredoc *herdoc, t_vars *vars)
{
	wait(&herdoc->child_status);
	if (WIFEXITED(herdoc->child_status))
		vars->exit_status = WEXITSTATUS(herdoc->child_status);
}

int	process_heredoc(t_list *temp, t_vars *vars, t_env **envir)
{
	t_heredoc	herdoc;

	init_heredoc(&herdoc);
	if (gen_file_name(&herdoc) == -1)
		return (-1);
	printf("%s\n", herdoc.file_name);
	herdoc.return_fork = fork();
	if (herdoc.return_fork < 0)
		return (-1);
	if (herdoc.return_fork == 0)
	{
		while (1)
		{
			herdoc.here_line = readline("> ");
			if (!herdoc.here_line)
			{
				free(herdoc.here_line);
				break ;
			}
			store_here(&herdoc, temp, envir, vars);
		}
		exit(0);
	}
	else
		child_exitstatus(&herdoc, vars);
	close(herdoc.fd);
	vars->heredoc_fd = herdoc.passed_fd;
	return (0);
}

