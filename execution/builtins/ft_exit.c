/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/20 14:31:24 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(int exit_status, int is_pipd)
{
	int	id;

	if (is_pipd)
	{
		id = fork();
		if (!id)
			exit(exit_status);
		else
			wait(NULL);
	}
	else
	{
		printf("exit\n");
		exit(exit_status);
	}
	return (0);
}
