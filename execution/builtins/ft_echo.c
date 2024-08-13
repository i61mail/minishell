/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:39 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/13 17:37:14 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isflag(char *str)
{
	if (!str || !(*str) || *str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(t_list *comm)
{
	t_list	*temp;
	int		is_n;

	is_n = 1;
	temp = NULL;
	comm = comm->next;
	if (ft_isflag(comm->content))
	{
		is_n = 0;
		comm = comm->next;
	}
	temp = comm;
	while (temp && temp->type == 0)
	{
		printf("%s", temp->content);
		if (temp->next)
			printf(" ");
		temp = temp->next;
	}
	if (is_n)
		printf("\n");
	return (0);
}
