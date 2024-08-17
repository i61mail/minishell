/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arewhat2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:07:31 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/17 11:31:30 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_expand(t_list *curr, char *str_temp, t_list **comm)
{
	curr = ft_lstnew(ft_strdup(str_temp), 0);
	ft_lstadd_back(comm, curr);
	free(str_temp);
}

char	*ft_check_env(t_env **envir, char *comp)
{
	char	*exp;
	t_env	*temp;

	temp = *envir;
	exp = NULL;
	while (temp && temp->key)
	{
		if (ft_strcmp(comp, temp->key) == 0)
		{
			exp = ft_strdup(temp->value);
			return (exp);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}

int	expanding(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	tmp[2];
	char	*comp;

	tmp[1] = '\0';
	comp = NULL;
	while (vars->read[*i] && (ft_isalpha(vars->read[*i]) || vars->read[*i] == '_'))
	{
		tmp[0] = vars->read[*i];
		comp = ft_strjoin(comp, tmp);
		if (!comp)
			return (-1);
		(*i)++;
	}
	comp = ft_check_env(envir, comp);
	if (!comp)
		return (-1);
	*str_temp = ft_strjoin(*str_temp, comp);
	return (0);
}

int	count_dollar(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i] == '$')
	{
		(*i)++;
		len++;
	}
	return (len);
}

int	dollar(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	int	len;
	char *temp;
	int	start;
	int	check;

	check = 0;
	start = 0;
	len = 0;
	temp = NULL;
	if (vars->read[*i] == '$')
	{
		start = *i;
		len = count_dollar(vars->read, i);
		if (len % 2 != 0)
		{
			if (ft_isdigit(vars->read[*i]))
			{
				check = 1;
				(*i)++;
			}
		}
		if (len % 2 != 0 && check == 0)
		{
			temp = ft_substr(vars->read, start, len - 1);
			expanding(vars, i, &temp, envir);
		}
		else
			temp = ft_substr(vars->read, start, len);
		*str_temp = ft_strjoin(*str_temp, temp);
	}
	return (0);
}

int	double_quo(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && vars->read[*i] != 34)
	{
		if (vars->read[*i] == '$')
			dollar(vars, i, str_temp, envir);
		else if (vars->read[*i] != 34)
		{
			temp[0] = vars->read[*i];
			*str_temp = ft_strjoin(*str_temp, temp);
			if (!*str_temp)
				return (-1);
			(*i)++;
		}
	}
	if (vars->read[*i] == 34)
		(*i) += 1;
	return (0);
}

int	single_quo(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[*i] == 39)
	{
		(*i)++;
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

int	just_alpha(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	temp[2];
	char	*str;

	(void)envir;
	str = NULL;
	temp[1] = '\0';
	while (vars->read[*i] && vars->read[*i] != '$' && !ft_issep(vars->read[*i]) && !ft_isquotes(vars->read[*i]))
	{
		temp[0] = vars->read[*i];
		str = ft_strjoin(str, temp);
		if (!str)
			return (-1);
		(*i)++;
	}
	*str_temp = ft_strjoin(*str_temp, str);
	return (0);
}

int	dollar_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	while (ft_isquotes(vars->read[*i]) || vars->read[*i] == '$' || ft_issep(vars->read[*i]))
	{
		if (vars->read[*i] == 34)
		{
			(*i)++;
			double_quo(vars, i, str_temp, envir);
		}
		if (vars->read[*i] == 39)
			single_quo(vars, i, str_temp);
		if (vars->read[*i] == '$')
			dollar(vars, i, str_temp, envir);
		if (!ft_issep(vars->read[*i] && vars->read[*i] != '$') && !ft_isquotes(vars->read[*i]))
			just_alpha(vars, i, str_temp, envir);
		if (ft_issep(vars->read[*i]) || ft_isspace(vars->read[*i]))
			return (2);
	}
	return (0);
}

int	ft_arequotes(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	temp[2];
	char	*str_temp;
	int		check;
	t_list	*curr;

	(void)comm;
	check = 0;
	temp[1] = '\0';
	curr = NULL;
	if (*i > 0 && !ft_isspace(vars->read[*i - 1])
		&& !ft_issep(vars->read[*i - 1]))
		*i = vars->befor_sing;
	while (vars->read[*i])
	{
		str_temp = NULL;
		while (vars->read[*i] && !ft_isquotes(vars->read[*i])
			&& vars->read[*i] != '$')
		{
			temp[0] = vars->read[*i];
			str_temp = ft_strjoin(str_temp, temp);
			if (!str_temp)
				return (-1);
			(*i)++;
		}
		check = dollar_quotes(vars, i, &str_temp, envir);
		if (check == -1)
			return (-1);
		replace_expand(curr, str_temp, comm);
		if (check == 2)
			break ;
	}
	return (0);
}
