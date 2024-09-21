/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arewhat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:52:49 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/21 12:15:28 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dollar(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	*temp;
	int		check;

	initi_vars(&check, &temp);
	if (vars->read[*i] == '$')
	{
		vars->start = *i;
		vars->len = count_dollar(vars->read, i);
		if (vars->len % 2 != 0)
			skip_digit(vars, i, &check);
		if (vars->len % 2 != 0 && check == 0)
		{
			append_dollar(vars, i, &temp, envir);
		}
		else if (vars->len % 2 != 0 && check == 1)
			temp = ft_substr(vars->read, vars->start, vars->len - 1);
		else
			temp = ft_substr(vars->read, vars->start, vars->len);
		if (temp)
			*str_temp = ft_strjoin(*str_temp, temp);
		free(temp);
		if (join_afterdollar(vars, i, str_temp) == -1)
			return (-1);
		if (address_quote(vars, i, str_temp, envir) == 2)
			return (2);
	}
	return (0);
}

int	adding(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
		&& !ft_isquotes(vars->read[*i]) && vars->read[*i] != '$')
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		(*i)++;
	}
	return (0);
}

static void	init_vars(char **str_temp, int *hold)
{
	*hold = 0;
	*str_temp = ft_strdup("");
	if (!str_temp)
		return ;
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	copie_to_node(char **str, t_list **comm, t_vars *vars)
{
	int b;
	char	*token = NULL;

	b = 0;
	char **s = ft_split_space(*str);
	int i = double_pointer(s);
	while (i - 1 > 0 && s[b])
	{
		token = ft_strdup(s[b]);
		ft_lstadd_back(comm, ft_lstnew(token, COMM));
		b++;
		i--;
	}
	char *string = ft_strstr(*str, s[b], &b);
		vars->befor_sing = vars->catsh + b;
	char	*temp2 = NULL;
		temp2 = ft_strjoin(temp2, string);
		b++;
	free(*str);
	*str = ft_strdup("");
	*str = ft_strjoin(*str, temp2);
}

int	ft_arealpha(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	*str_temp;
	int		hold;
	char	temp[2];
	int		type;

	init_vars(&str_temp, &hold);
	temp[1] = '\0';
	type = 0;
	vars->catsh = *i;
	vars->befor_sing = *i;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
			&& !ft_isquotes(vars->read[*i]) && vars->read[*i] != '$')
		{
			temp[0] = vars->read[*i];
			str_temp = ft_strjoin(str_temp, temp);
			(*i)++;
		}
		else
		{
			if (vars->read[*i] == '$')
			{
				if (*i > 0 && (ft_isalpha(vars->read[*i - 1]) || vars->read[*i - 1] == '_' || ft_isspace(vars->read[*i - 1])))
					type = SPLITED;
				else if (*i == 0 && vars->read[*i] == '$')
					type = SPLITED;
				hold = ft_dollar(vars, i, &str_temp, envir);
				if (hold == 2)
				{
					int k = check_space(str_temp);
					if (k == 1)
					{
						vars->befo_qu = *i;
						copie_to_node(&str_temp, comm, vars);
						vars->befor = ft_strdup(str_temp);
					}
					return (2);
				}
				if (sspace(str_temp) == 0 && vars->check_ambiguous == 1)
					type = AMBIGUOUS;
				replace_expand(str_temp, comm, type);
				return (0);
			}
			else
				break ;
		}
	}
	if (vars->read[*i] && ft_isquotes(vars->read[*i]))
		return (2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (free(str_temp), 0);
}
