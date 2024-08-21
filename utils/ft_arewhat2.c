/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arewhat2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:07:31 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/21 11:36:09 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_expand(t_list *curr, char *str_temp, t_list **comm)
{
	if (!str_temp)
		str_temp = ft_strdup("");
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

int	expanding(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	tmp[2];
	char	*comp;

	tmp[1] = '\0';
	comp = NULL;
	while (vars->read[*i] && (ft_isalpha(vars->read[*i]) || vars->read[*i] == '_' || ft_isdigit(vars->read[*i])))
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
	return (free(comp), 0);
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

int	isthere(t_vars *vars, int *i)
{
	int b;
	int	check;

	check = 0;
	b = vars->bef_spac;
	while (vars->read[b] && b != *i)
	{
		if (vars->read[b] && vars->read[b] == 34 && check == 0 && *i > b)
		{
			check = 1;
			b++;
		}
		while (vars->read[b] && check == 1 && (ft_isalpha(vars->read[b]) || ft_isdigit(vars->read[b]) || vars->read[b] == '_' || ft_isspace(vars->read[b])))
		{
			b++;
			if (vars->read[b] && vars->read[b] == '$')
				return (1);
		}
		if (vars->read[b] && vars->read[b] == 34 && check == 1 && b > *i)
			return (1);
		if (vars->read[b] && vars->read[b] == 34 && check == 1)
			return (0);
		if (vars->read[b] && vars->read[b] == 39 && check == 1)
			return (1);
		b++;
		if (b > *i + 1)
			return (0);
	}
	if (vars->read[b] && b == *i && (!ft_isquotes(vars->read[b + 1]) && vars->read[b + 1] != '_'
		&& !ft_isdigit(vars->read[b + 1]) && !ft_isalpha(vars->read[b + 1])))
		return (1);
	return (0);
}

int	ft_onedollar(char *str, int *i)
{
	if (str[*i] && str[*i] == 34)
		(*i)++;
	if (str[*i] && str[*i] == '$')
	{
		if (str[*i + 1] == 34)
			return (1);
		else
			return (0);
	}
	return (0);
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
		if (vars->read[*i + 1] != '$' && !ft_isdigit(vars->read[*i + 1]) && !ft_isalpha(vars->read[*i + 1]) && vars->read[*i + 1] != '_')
		{
			if (*i > 0 && vars->read[*i] && (vars->read[*i + 1] == '\0' || isthere(vars, i)))
				*str_temp = ft_strjoin(*str_temp, "$\0");
			else if (*i > 0 && vars->read[*i] && ft_isquotes(vars->read[*i + 1] && isthere(vars, i)))
				*str_temp = ft_strjoin(*str_temp, "$\0");
		}
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
		else if (len % 2 != 0 && check == 1)
			temp = ft_substr(vars->read, start, len - 1);
		else
			temp = ft_substr(vars->read, start, len);
		*str_temp = ft_strjoin(*str_temp, temp);
		free(temp);
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
	{
		(*i) += 1;
		vars->bef_spac = *i;
	}
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
	free(str);
	return (0);
}

int	dollar_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	while (vars->read[*i] && (ft_isquotes(vars->read[*i]) || vars->read[*i] == '$' || ft_issep(vars->read[*i])))
	{
		if (vars->read[*i] == 34)
		{
			(*i)++;
			double_quo(vars, i, str_temp, envir);
		}
		if (vars->read[*i] && vars->read[*i] == 39)
			single_quo(vars, i, str_temp);
		if (vars->read[*i] && vars->read[*i] == '$')
			dollar(vars, i, str_temp, envir);
		if (vars->read[*i] && !ft_issep(vars->read[*i]) && vars->read[*i] != '$' && !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i]))
			just_alpha(vars, i, str_temp, envir);
		if (vars->read[*i] && (ft_issep(vars->read[*i]) || ft_isspace(vars->read[*i])))
			return (2);
	}
	return (0);
}

static int	before_quotes(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && !ft_isquotes(vars->read[*i])
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

int	ft_arequotes(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	*str_temp;
	int		check;
	t_list	*curr;

	check = 0;
	curr = NULL;
	if (*i > 0 && !ft_isspace(vars->read[*i - 1])
		&& !ft_issep(vars->read[*i - 1]))
		*i = vars->befor_sing;
	while (vars->read[*i])
	{
		str_temp = NULL;
		if (before_quotes(vars, i, &str_temp) == -1)
			return (-1);
		check = dollar_quotes(vars, i, &str_temp, envir);
		if (check == -1)
			return (-1);
		replace_expand(curr, str_temp, comm);
		if (check == 2)
			break ;
	}
	return (0);
}
