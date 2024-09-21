/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:30:37 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/21 13:08:44 by i61mail          ###   ########.fr       */
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

char	*ft_strstr(char *str, char *to_find, int *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
		{
			*b = i;
			return (str + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
