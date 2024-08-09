/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arewhat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:52:49 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/09 14:45:08 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes(t_vars *vars, int *i, t_list **comm)
{
	if (ft_isquotes(vars->read[*i]))
	{
		if (even_odd(vars->read) == 0)
		{
			ft_error(comm);
			return (-1);
		}
		ft_arequotes(vars, i, comm);
	}
	return (0);
}

int	ft_arealpha(t_vars *vars, int *i, t_list **comm)
{
	vars->catsh = *i;
	vars->befor_sing = *i;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
			&& !ft_isquotes(vars->read[*i]))
			(*i)++;
		else
			break ;
	}
	if (ft_isquotes(vars->read[*i]))
		return (2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (0);
}

int	ft_arespace(char *read, int *i)
{
	while (read[*i])
	{
		if (ft_isspace(read[*i]))
			(*i)++;
		else
			break ;
	}
	return (0);
}

static int	ft_aresep3(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == 1 || type == 2) //redirection '<' && '>'
	{
		vars->catsh = *i;
		if (type == 1)
		{
			check = ft_redirec(vars, i, '<', comm);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
		else
		{
			check = ft_redirec(vars, i, '>', comm);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
	}
	return (0);
}

static int	ft_aresep2(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == 3) //append >>
	{
		vars->catsh = *i;
		check = ft_append(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == 4) // heredoc <<
	{
		vars->catsh = *i;
		check = ft_heredoc(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	if (ft_aresep3(vars, i, type, comm) == -1)
		return (-1);
	return (0);
}

int	ft_aresep(t_vars *vars, int *i, t_list **comm)
{
	int	type;
	int	check;

	type = 0;
	if (ft_check_type(vars->read, i, &type) == -1)
	{
		ft_error(comm);
		return (-1);
	}
	if (type == 5) //pipe
	{
		vars->catsh = *i;
		check = ft_pipe(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	if (ft_aresep2(vars, i, type, comm) == -1)
		return (-1);
	if (ft_token(vars, *i, comm, type) == -1)
		return (-1);
	return (0);
}

int	ft_count_dollar(char *str, int *i)
{
	int	k;

	k = 0;
	(*i)--;
	while (str[*i] == '$')
	{
		(*i)++;
		k++;
	}
	if (k % 2 == 0)
		return (k);
	else
		return (k - 1);
	return (0);
}

int	double_quo(t_vars *vars, int *i, char **str_temp)
{
	char temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && vars->read[*i] != '$' && vars->read[*i] != 34)
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	if (vars->read[*i] == 34)
		(*i) += 1;
	return (0);
}

int	single_quo(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[(*i)++] == 39)
	{
		while (vars->read[*i] && vars->read[*i] != 39)
		{
			temp[0] = vars->read[*i];
			*str_temp = ft_strjoin(*str_temp, temp);
			if (!*str_temp)
				return (-1);
			(*i)++;
		}
		(*i)++;
	}
	return (0);
}


int	dollar(t_vars *vars, int *i, char **str_temp)
{
	int	catsh;
	int	len;
	char *temp;
	
	temp = NULL;
	len = 0;
	catsh = 0;
	if (vars->read[*i] == '$')
	{
		(*i)++;
		if (vars->read[*i] == '$')
		{
			catsh = *i - 1;
			len = ft_count_dollar(vars->read, i);
			temp = ft_substr(vars->read, catsh, len);
			if (!temp)
				return (-1);
			*str_temp = ft_strjoin(*str_temp, temp);
			if (!*str_temp)
				return (-1);
		}
		if (ft_isdigit(vars->read[*i]))
			(*i)++;
		if (double_quo(vars, i, str_temp) == -1)
			return (-1);
	}
	return (0);
}
//"''"ks
//"'>'"ls|cat
//'ls''sd'>ls
//'ls'|'sd'ls
int	dollar_quotes(t_vars *vars, int *i, char **str_temp)
{
	if (dollar(vars, i, str_temp) == -1)
			return (-1);
	while (ft_isquotes(vars->read[*i]))
	{
		if (vars->read[*i] == 39)
		{
			if (single_quo(vars, i, str_temp))
				return (-1);
			if (ft_isspace(vars->read[*i]))
				return (2);
			if (ft_issep(vars->read[*i]))
				return (2);
		}
		if (vars->read[*i] == 34)
		{
			(*i)++;
			if (double_quo(vars, i, str_temp))
				return (-1);
			if (ft_isspace(vars->read[*i]))
				return (2);
			if (ft_issep(vars->read[*i]))
				return (2);
		}
	}
	return (0);
}

int	ft_arequotes(t_vars *vars, int *i, t_list **comm)
{
	(void)comm;
	char temp[2];
	char *str_temp;
	int	check;
	t_list *curr;

	check = 0;
	temp[1] = '\0';
	if (*i > 0 && !ft_isspace(vars->read[*i - 1]) && !ft_issep(vars->read[*i - 1]))
		*i = vars->befor_sing;
	while (vars->read[*i])
	{
		str_temp = NULL;
		while (vars->read[*i] && !ft_isquotes(vars->read[*i]) && vars->read[*i] != '$')
		{
			temp[0] = vars->read[*i];
			str_temp = ft_strjoin(str_temp, temp);
			if (!str_temp)
				return (-1);
			(*i)++;
		}
		check = dollar_quotes(vars, i, &str_temp);
		if (check == -1)
			return (-1);
		curr = ft_lstnew(ft_strdup(str_temp), 6);
		ft_lstadd_back(comm, curr);
		free(str_temp);
		if (check == 2)
			break;
	}
	return (0);
}
