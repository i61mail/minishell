/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:09:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/17 19:48:24 by isrkik           ###   ########.fr       */
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

void	f(void)
{
	system("leaks minishell");
}

void	init_vars(t_list **comm, t_vars *vars, t_env **envir)
{
	*envir = NULL;
	*comm = NULL;
	vars->read = NULL;
	vars->catsh = 0;
	vars->befor_sing = 0;
	vars->curr = NULL;
}

int	pars_exec(t_vars vars, t_list *comm, t_env *envir)
{
	add_history(vars.read);
	if (ft_pars_comm(&vars, &comm, &envir) != -1)
		ft_execute(&vars,comm,envir);
	// ft_pars_comm(&vars, &comm, &envir);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_list	*comm;
	t_vars	vars;
	t_env	*envir;

	atexit(f);
	(void)av;
	while (1)
	{
		init_vars(&comm, &vars, &envir);
		strcpy_env(&envir, env);
		if (ac == 1)
		{
			vars.read = readline("minishell> ");
			if (!vars.read)
			{
				free(vars.read);
				ft_lstfree(&comm);
				ft_env_free(&envir);
				break ;
			}
			pars_exec(vars, comm, envir);
		}
		else
		{
			ft_env_free(&envir);
			break ;
		}
		free(vars.read);
		ft_env_free(&envir);
		ft_lstfree(&comm);
	}
	return (0);
}
