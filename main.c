/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:09:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 22:15:35 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pars_comm(t_vars *vars, t_list **comm, t_env **envir)
{
	int		i;

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
			if (ft_aresep(vars, &i, comm, envir) == -1)
				return (is_sep(vars));
			if (vars->exit_status == 130 && vars->is_signal == 1)
				break ;
		}
		if (quotes(vars, &i, comm, envir) == -1)
			return (-1);
	}
	return (0);
}

int	pars_exec(t_vars *vars, t_list *comm, t_env **envir)
{
	add_history(vars->read);
	if (ft_pars_comm(vars, &comm, envir) != -1)
	{
		// t_list *temp = comm;
		// while (temp)
		// {
		// 	printf("c:%s,t:%d\n", temp->content, temp->type);
		// 	temp = temp->next;
		// }
		ft_execute(vars, comm, envir);
		free(vars->read);
	}
	else
		free(vars->read);
	return (0);
}

void	ft_readline_test(t_vars *vars, t_list *comm, t_env **envir, int ac, char **av)
{

	if (ac == 3)
	{
		vars->read = ft_strdup(av[2]);
		if (!vars->read)
		{
			return ;
		}
		pars_exec(vars, comm, envir);
	}
}

void	ft_readline(t_vars *vars, t_list *comm, t_env **envir, int ac)
{
	while (1)
	{
		tcsetattr(0, 0, &vars->reset);
		if (ac == 1)
		{
			vars->read = readline("minishell> ");
			if (!vars->read)
			{
				ft_putstr_fd("exit\n", 1);
				break ;
			}
			pars_exec(vars, comm, envir);
		}
		else
		{
			ft_env_free(envir);
			break ;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_list	*comm;
	t_vars	vars;
	t_env	*envir;

	(void)av;
	main_init_vars(&comm, &vars, &envir, env);
	tcgetattr(0, &vars.reset);
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	// ft_readline(&vars, comm, &envir, ac);
	ft_readline_test(&vars, comm, &envir, ac, av);
	exit(vars.exit_status);
}
//exit 3 cv " "