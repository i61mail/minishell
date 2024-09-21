/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:26 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/21 13:43:14 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_expand(char *str_temp, t_list **comm, int type)
{
	if (str_temp && str_temp[0] == '\0')
	{
		type = AMBIGUOUS;
		str_temp = ft_strdup("");
	}
	else if (!str_temp)
	{
		str_temp = ft_strdup("");
	}
	ft_lstadd_back(comm, ft_lstnew(ft_strdup(str_temp), type));
	free(str_temp);
}

char	*ft_check_env(t_env **envir, char *comp)
{
	char	*exp;
	t_env	*temp;

	temp = *envir;
	exp = NULL;
	if (!comp)
		return (NULL);
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

int	expand_exit_status(t_vars *vars, char **comp, int *i, char **temp)
{
	*comp = ft_itoa(vars->exit_status);
	*temp = ft_strjoin(*temp, *comp);
	(*i)++;
	return (0);
}

int	expanding(t_vars *vars, int *i, char **temp, t_env **envir)
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
		return (expand_exit_status(vars, &comp, i, temp));
	comp = ft_check_env(envir, comp);
	if (comp)
		*temp = ft_strjoin(*temp, comp);
	if (*temp[0] == '\0')
	{
		free(*temp);
		*temp = NULL;
	}
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
		{
			if (*i > 0 && (ft_isalpha(vars->read[*i - 1]) || vars->read[*i - 1] == '_'))
				vars->flag_splite = SPLITED;
			dollar(vars, i, str_temp, envir);
		}
		if (vars->read[*i] && !ft_issep(vars->read[*i]) && vars->read[*i] != '$'
			&& !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i]))
			just_alpha(vars, i, str_temp, envir);
		if (vars->read[*i] && (ft_issep(vars->read[*i])
				|| ft_isspace(vars->read[*i])))
			return (2);
	}
	return (0);
}
