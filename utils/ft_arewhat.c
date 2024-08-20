/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arewhat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:52:49 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/20 22:18:15 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dollar(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	int	len;
	char *temp;
	int	start;
	int	check;
	char stemp[2];

	check = 0;
	stemp[1] = '\0';
	start = 0;
	len = 0;
	temp = NULL;
	if (vars->read[*i] == '$')
	{
		if (vars->read[*i + 1] == '\0' || ft_isspace(vars->read[*i + 1]))
			*str_temp = ft_strjoin(*str_temp, "$\0");
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
		while (vars->read[*i] && !ft_isspace(vars->read[*i]) && !ft_issep(vars->read[*i]) && vars->read[*i] != '$' && !ft_isquotes(vars->read[*i]))
		{
			stemp[0] = vars->read[*i];
			*str_temp = ft_strjoin(*str_temp, stemp);
			(*i)++;
		}
		if (vars->read[*i] == '$')
			return (ft_dollar(vars, i, str_temp, envir));
		if (ft_isquotes(vars->read[*i]))
			return (free(*str_temp), 2);
	}
	return (0);
}

int	ft_arealpha(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char *str_temp;
	t_list	*curr;
	int		hold;
	char	temp[2];

	temp[1] = '\0';
	hold = 0;
	curr = NULL;
	str_temp = ft_strdup("");
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
				hold = ft_dollar(vars, i, &str_temp, envir);
				if (hold == 2)
					return (2);
				replace_expand(curr, str_temp, comm);
				return (0);
			}
			else
				break ;
		}
	}
	if (vars->read[*i] && ft_isquotes(vars->read[*i]))
		return (free(str_temp), 2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (free(str_temp), 0);
}

int	ft_arespace(t_vars *vars, int *i)
{
	vars->bef_spac = *i;
	while (vars->read[*i])
	{
		if (ft_isspace(vars->read[*i]))
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
	if (type == 1 || type == 2)
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
	if (type == 3)
	{
		vars->catsh = *i;
		check = ft_append(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == 4)
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
	if (type == 5)
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
