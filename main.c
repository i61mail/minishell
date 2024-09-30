/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:09:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/30 17:57:03 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_search(t_vars *vars, t_list *comm)
{
	while (comm && comm->content)
	{
		if (comm->type != RED_IN && comm->type != RED_OUT
			&& comm->type != HEREDOC && comm->type != RED_APPEND
			&& comm->type != PIP)
		{
			free(vars->last_arg);
			vars->last_arg = ft_strdup(comm->content);
		}
		else
			break ;
		comm = comm->next;
	}
}

int	ft_pars_comm(t_vars *vars, t_list **comm, t_env **envir)
{
	int		i;

	i = 0;
	vars->check_ambiguous = 0;
	vars->is_signal = 0;
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
				return (-1);
			if (vars->exit_status == 130)
				break ;
		}
		if (quotes(vars, &i, comm, envir) == -1)
			return (-1);
	}
	return (0);
}

int	three_vars(t_env **envir)
{
	add_to_node(ft_strdup("PWD"),
		ft_strdup("/Users/isrkik/Desktop/minishell"), envir);
	add_to_node(ft_strdup("PATH"),
		ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki:/Library/Apple/usr/bin"), envir);
	add_to_node(ft_strdup("SHLVL"),
		ft_strdup("0"), envir);
	add_to_node(ft_strdup("_"),
		ft_strdup("/usr/bin/env"), envir);
	add_to_node(ft_strdup("OLDPWD"), NULL, envir);
	return (1);
}

void	warning_error(long long *increm)
{
	ft_putstr_fd("warning: shell level (", 2);
	ft_putnbr_fd(*increm, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
	*increm = 1;
}

void	shell_level_utils(int *is, long long *old_increm,
							long long *increm, t_env *env)
{
	*is = 1;
	*old_increm = ft_atoi(env->value);
	*increm = *old_increm + 1;
	if (*increm > 2147483647 || *increm < 0)
		*increm = 0;
}

static void	init_shell(long long *increm, int *is, long long *old_increm)
{
	*increm = 0;
	*is = 0;
	*old_increm = 0;
}

int	shell_level(t_env **envir)
{
	t_env		*env;
	long long	increm;
	long long	old_increm;
	int			is;

	init_shell(&increm, &is, &old_increm);
	env = *envir;
	while (env)
	{
		if (ft_strncmp(env->key, "SHLVL\0", 6) == 0)
		{
			shell_level_utils(&is, &old_increm, &increm, env);
			if (increm == 1000)
			{
				free(env->value);
				env->value = "";
				increm = 0;
				return (0);
			}
			else if (increm > 1000)
				warning_error(&increm);
			free(env->value);
			env->value = ft_itoa(increm);
		}
		env = env->next;
	}
	if (is == 0)
		add_to_node(ft_strdup("SHLVL"), ft_strdup("1"), envir);
	return (0);
}

void	init_vars2(t_vars *vars)
{
	vars->catsh = 0;
	vars->befor_sing = 0;
	vars->bef_spac = 0;
	vars->builtin = 0;
	vars->len = 0;
	vars->start = 0;
	vars->exit_status = 0;
	vars->old_fd = 0;
	vars->pipe = 0;
	vars->numofpipes = 0;
	vars->heredoc_fd = 0;
	vars->flag_splite = 0;
	vars->quoted = 0;
	vars->del_type = 0;
	vars->cmd_num = 0;
	vars->cd = 0;
	vars->atoifail = 0;
	vars->check_ambiguous = 0;
	vars->env_i = 0;
	vars->not_pass = 0;
	vars->bef_dollar = 0;
	vars->old_pwd = 0;
}

void	init_vars(t_list **comm, t_vars *vars, t_env **envir, char **env)
{
	init_vars2(vars);
	*envir = NULL;
	*comm = NULL;
	vars->read = NULL;
	vars->token = NULL;
	vars->befor = NULL;
	vars->last_arg = NULL;
	strcpy_env(envir, env);
	if (!*envir)
		vars->env_i = three_vars(envir);
	shell_level(envir);
}

int	pars_exec(t_vars *vars, t_list *comm, t_env **envir)
{
	add_history(vars->read);
	if (ft_pars_comm(vars, &comm, envir) != -1)
	{
		// if (comm)
		comm = ft_execute(vars, comm, envir);
		free(vars->read);
	}
	else
		free(vars->read);
	return (0);
}

void	handle_ctrlc(int sig)
{
	(void)sig;
	if (ft_catch(1, 2) == 2)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (ft_catch(1, 5) == 5)
		return ;
	ft_catch(2, 4);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
	init_vars(&comm, &vars, &envir, env);
	tcgetattr(0, &vars.reset);
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	ft_readline(&vars, comm, &envir, ac);
	exit(vars.exit_status);
}

//env -i ./minishell
//./minishell
//two heredocs got a leak
//$''