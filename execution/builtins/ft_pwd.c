/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:28:00 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/18 23:17:39 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
		return (perror("getcwd"), errno);
	write(1, pwd, ft_strlen(pwd));
	ft_putchar_fd('\n', 1);
	exit(0);
	return (0);
}
