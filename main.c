/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:09:34 by isrkik            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/22 16:08:13 by mait-lah         ###   ########.fr       */
=======
/*   Updated: 2024/08/22 15:52:46 by isrkik           ###   ########.fr       */
>>>>>>> pars
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_arespace(vars, &i);
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

void	init_vars(t_list **comm, t_vars *vars, t_env **envir, char **env)
{
	*envir = NULL;
	*comm = NULL;
	vars->read = NULL;
	vars->catsh = 0;
	vars->befor_sing = 0;
	vars->bef_spac = 0;
	vars->len = 0;
	vars->start = 0;
	strcpy_env(envir, env);
}

int	pars_exec(t_vars vars, t_list *comm, t_env *envir)
{
	add_history(vars.read);
	if (ft_pars_comm(&vars, &comm, &envir) != -1)
	{
		ft_execute(&vars, comm, envir);
		free_all(vars.read, &comm, &envir);
	}
	else
	{
		free(vars.read);
		ft_env_free(&envir);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_list	*comm;
	t_vars	vars;
	t_env	*envir;

	(void)av;
	while (1)
	{
		init_vars(&comm, &vars, &envir, env);
		if (ac == 1)
		{
			vars.read = readline("minishell> ");
			if (!vars.read)
			{
				free_all(vars.read, &comm, &envir);
				break ;
			}
			pars_exec(vars, comm, envir);
		}
		else
		{
			ft_env_free(&envir);
			break ;
		}
	}
	return (0);
}
