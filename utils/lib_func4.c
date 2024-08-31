/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:48:32 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/31 12:57:46 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check(unsigned long long result, int i, char *str, int sign)
{
	if (sign == -1 && result == 9223372036854775808ULL)
	{
		if (ft_isdigit(str[i]) == 1)
			return (-1);
		return (1);
	}
	if (result > LLONG_MAX)
		return (-1);
	return (0);
}

long long	ft_atoi(char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (-1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i++] - 48;
		if (ft_check(result, i, str, sign) == -1)
			return (-1);
		else if (ft_check(result, i, str, sign) == 1)
			return (result * sign);
	}
	return (result * sign);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1337);
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_count(int n)
{
	int b;

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

char *ft_itoa(int nbr)
{
	char *str;
	long long convert;
	int	sign;
	int len_str;

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
