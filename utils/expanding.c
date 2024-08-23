/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:26 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/23 18:08:08 by isrkik           ###   ########.fr       */
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

char *expand_exit_status(t_vars *vars, char *comp)
{
	comp = ft_itoa(vars->exit_status);
	return (comp);
}

int	expanding(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	tmp[2];
	char	*comp;

	tmp[1] = '\0';
	comp = NULL;
	while (vars->read[*i] && (ft_isalpha(vars->read[*i])
			|| vars->read[*i] == '_' || ft_isdigit(vars->read[*i])))
	{
		tmp[0] = vars->read[*i];
		comp = ft_strjoin(comp, tmp);
		if (!comp)
			return (-1);
		(*i)++;
	}
	if (vars->read[*i] == '?')
	{
		comp = expand_exit_status(vars, comp);
		*str_temp = ft_strjoin(*str_temp, comp);
		(*i)++;
		return (0);
	}
	comp = ft_check_env(envir, comp);
	if (!comp)
		return (-1);
	*str_temp = ft_strjoin(*str_temp, comp);
	return (free(comp), 0);
}

void	init_va(int *check, char **temp)
{
	*check = 0;
	*temp = NULL;
}

int	dollar_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	while (vars->read[*i] && (ft_isquotes(vars->read[*i])
			|| vars->read[*i] == '$' || ft_issep(vars->read[*i])))
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
		if (vars->read[*i] && !ft_issep(vars->read[*i]) && vars->read[*i] != '$'
			&& !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i]))
			just_alpha(vars, i, str_temp, envir);
		if (vars->read[*i] && (ft_issep(vars->read[*i])
				|| ft_isspace(vars->read[*i])))
			return (2);
	}
	return (0);
}
