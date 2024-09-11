/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redircmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:03:19 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/08 00:51:29 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redircmp(char *s1, char *s2, int *i)
{
	int	c;
	int	k;

	k = 0;
	c = *i;
	while (s2[k])
	{
		if (s1[c] == s2[k])
		{
			c++;
			k++;
		}
		else
			return (-1);
	}
	return (1);
}
