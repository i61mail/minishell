/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:38:21 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/28 18:17:27 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_digit_here(t_heredoc *herdoc, int *i, int *check)
{
	if (ft_isdigit(herdoc->here_line[*i]))
	{
		*check = 1;
		(*i)++;
	}
}

int	ft_catch(int type, int value)
{
	static int	var;

	if (type == 0)
	{
		var = value;
		return (var);
	}
	else if (type == 1)
		return (var);
	if (type == 2)
	{
		var = value;
		return (var);
	}
	else if (type == 3)
		return (var);
	if (type == 4)
	{
		var = value;
		return (var);
	}
	else if (type == 4)
		return (var);
	return (-1);
}

int	printable_char(char *str, int *i, char **file_name)
{
	char	temp[2];

	temp[1] = '\0';
	if (ft_isprint(str[*i]) && (ft_isalpha(str[*i]) || ft_isdigit(str[*i])))
	{
		temp[0] = str[*i];
		*file_name = ft_strjoin(*file_name, temp);
		if (!*file_name)
			return (-1);
	}
	return (0);
}

int	read_devrandom(int fd, char **file_name)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * 101);
	if (!str)
		return (-1);
	str[100] = '\0';
	if (read(fd, str, 100) == -1)
		return (-1);
	while (i < 40)
	{
		if (printable_char(str, &i, file_name) == -1)
			return (-1);
		i++;
	}
	free(str);
	*file_name = ft_strjoin(*file_name, ".txt");
	if (!*file_name)
		return (-1);
	return (0);
}

int	gen_file_name(t_heredoc *herdoc)
{
	herdoc->fd = open("/dev/random", O_RDONLY);
	if (herdoc->fd < 0)
		return (-1);
	if (read_devrandom(herdoc->fd, &herdoc->file_name) == -1)
		return (-1);
	close(herdoc->fd);
	herdoc->fd = open(herdoc->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	herdoc->passed_fd = open(herdoc->file_name, O_RDWR | O_TRUNC, 0644);
	unlink(herdoc->file_name);
	free(herdoc->file_name);
	if (herdoc->fd < 0 || herdoc->passed_fd < 0)
		return (-1);
	return (0);
}
