/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:30:37 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/15 14:54:04 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	chr;

	chr = (unsigned char )c;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == chr)
			return ((char *)&str[i]);
		i++;
	}
	if (str && str[i] == chr)
		return ((char *)&str[i]);
	return (NULL);
}