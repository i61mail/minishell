/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/27 03:58:00 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *envir)
{
	t_env *temp;

	temp = envir;
	while (temp)
	{
		if (temp->value)
			printf("%s=\"%s\"\n",temp->key, temp->value);
		temp = temp->next;
	}
}
