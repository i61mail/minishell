/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:09:22 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 15:11:01 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
