/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:08:14 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 15:40:02 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_init_vars2(t_vars *vars)
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
	vars->is_red = 0;
	vars->type = 0;
}

void	main_init_vars(t_list **comm, t_vars *vars, t_env **envir, char **env)
{
	main_init_vars2(vars);
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
