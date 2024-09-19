/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:54:35 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/19 14:24:06 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token(t_vars *vars, int i, t_list **comm, int type)
{
	char	*token;
	t_list	*current;

	token = ft_substr(vars->read, vars->catsh, i - vars->catsh);
	if (!token)
		return (-1);
	current = ft_lstnew(token, type);
	if (!current)
		return (free(token), free(current), -1);
	ft_lstadd_back(comm, current);
	if (!*comm)
		return (free(token), free(current), -1);
	return (0);
}

void	ft_error(t_list **comm, t_vars *vars)
{
	vars->exit_status = 258;
	ft_putstr_fd("minishell: syntax error\n", 2);
	ft_lstfree(comm);
	return ;
}

int	ft_check_type(char *read, int *i, int *type)
{
	int	c;

	c = *i;
	if (read[c] == '|')
		*type = PIP;
	else if (ft_redircmp(read, ">>", i) == 1)
		*type = RED_APPEND;
	else if (ft_redircmp(read, "<<", i) == 1)
		*type = HEREDOC;
	else if (read[c] == '<')
		*type = RED_IN;
	else if (read[c] == '>')
		*type = RED_OUT;
	else
		return (-1);
	return (0);
}

void	free_all(char *read, t_list **comm, t_env **envir)
{
	free(read);
	(void)comm;
	// ft_lstfree(comm);
	ft_env_free(envir);
}

int	just_alpha(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	temp[2];
	char	*str;

	(void)envir;
	str = NULL;
	temp[1] = '\0';
	while (vars->read[*i] && vars->read[*i] != '$'
		&& !ft_issep(vars->read[*i]) && !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i]))
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
