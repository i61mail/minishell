/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:50:55 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 17:43:50 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count(int n)
{
	int	b;

	b = 0;
	while (n != 0)
	{
		n /= 10;
		b++;
	}
	return (b);
}

char	*ft_int_to_str(long long convert, int len_str, char *str)
{
	if (convert < 0)
	{
		str[0] = '-';
		convert *= -1;
		str[len_str + 1] = '\0';
		while (len_str > 0)
		{
			str[len_str] = convert % 10 + 48;
			convert /= 10;
			len_str--;
		}
	}
	else if (convert > 0)
	{
		str[len_str] = '\0';
		while (len_str)
		{
			str[len_str - 1] = convert % 10 + 48;
			convert /= 10;
			len_str--;
		}
	}
	return (str);
}

char	*ft_itoa(int nbr)
{
	char		*str;
	long long	convert;
	int			sign;
	int			len_str;

	len_str = ft_count(nbr);
	convert = (long long) nbr;
	sign = 0;
	if (convert < 0)
		sign = 1;
	else if (convert == 0)
		return ("0");
	str = malloc(sizeof(char) * (len_str + sign + 1));
	if (!str)
		return (NULL);
	return (ft_int_to_str(convert, len_str, str));
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

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
