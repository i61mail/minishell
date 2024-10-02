/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:03:56 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 15:10:56 by isrkik           ###   ########.fr       */
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

int	is_sep(t_vars *vars)
{
	if (vars->is_signal == 1)
		close(vars->heredoc_fd);
	return (-1);
}

int	three_vars(t_env **envir, t_vars *vars)
{
	if (!my_getenv("PWD", *envir))
		add_to_node(ft_strdup("PWD"),
			ft_strdup("/Users/isrkik/Desktop/minishell"), envir);
	if (!my_getenv("PATH", *envir))
	{
		add_to_node(ft_strdup("PATH"),
			ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"), envir);
		vars->env_i = 1;
	}
	if (!my_getenv("SHLVL", *envir))
		add_to_node(ft_strdup("SHLVL"),
			ft_strdup("0"), envir);
	if (!my_getenv("_", *envir))
		add_to_node(ft_strdup("_"),
			ft_strdup("/usr/bin/env"), envir);
	if (!my_getenv("OLDPWD", *envir))
		add_to_node(ft_strdup("OLDPWD"), NULL, envir);
	return (1);
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
