/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:09:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/16 11:22:24 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_pars_comm(t_vars *vars, t_list **comm, t_env **envir)
{
	int		i;
	// t_list	*temp;

	i = 0;
	while (vars->read[i] != '\0')
	{
		if (!ft_issep(vars->read[i])
			&& !ft_isspace(vars->read[i]) && !ft_isquotes(vars->read[i]))
			ft_arealpha(vars, &i, comm, envir);
		else if (ft_isspace(vars->read[i]))
			ft_arespace(vars->read, &i);
		else if (ft_issep(vars->read[i]))
		{
			if (ft_aresep(vars, &i, comm) == -1)
				return (-1);
		}
		if (quotes(vars, &i, comm, envir) == -1)
			return (-1);
	}
	// temp = *comm;
	// while (temp)
	// {
	// 	printf("%s      &&    %d\n", temp->content, temp->type);
	// 	temp = temp->next;
	// }
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_list	*comm;
	t_vars	vars;
	t_env	*envir;

	(void)av;
	envir = NULL;
	strcpy_env(&envir, env);
	while (1)
	{
		comm = NULL;
		if (ac == 1)
		{
			vars.read = readline("minishell> ");
			if (!vars.read)
			{
				free(vars.read);
				break ;
			}
			add_history(vars.read);
			ft_pars_comm(&vars, &comm, &envir);
			ft_execute(&vars,comm,envir);
		}
		else
			break ;
		free(vars.read);
	}
	free(vars.read);
	return (0);
}
