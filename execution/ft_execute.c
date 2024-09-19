/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/19 12:37:05 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char *str, t_env *envir)
{
	t_env	*temp;

	temp = envir;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd\0") || !ft_strcmp(command, "echo\0")
		|| !ft_strcmp(command, "env\0")
		|| !ft_strcmp(command, "exit\0") || !ft_strcmp(command, "export\0")
		|| !ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "unset\0"))
		return (1);
	return (0);
}

int	ft_invalid_bin(char *binary, t_list *comm, t_vars *vars)
{
	struct stat	path;

	if (!binary)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(comm->content, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(comm->content);
		free(comm);
		vars->exit_status = 127;
		return (1);
	}
	stat(binary, &path);
	if (S_ISDIR(path.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": is a directory\n", 2);
		vars->exit_status = 126;
		return (1);
	}
	if (S_ISREG(path.st_mode) && access(binary, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		vars->exit_status = 126;
		return (1);
	}
	if (access(binary, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		vars->exit_status = 127;
		return (1);
	}
	return (0);
}

void	ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*binary;
	char	**_2denv;

	dup_and_close(vars->pfd[1], 1);
	dup_and_close(vars->old_fd, 0);
	if (vars->pfd[0] != 0 && vars->pfd[0] != 1)
		close(vars->pfd[0]);
	while (comm && comm->type == AMBIGUOUS)
		comm = comm->next;
	if (!comm)
		exit(0);
	binary = ft_locate_bin(comm->content, my_getenv("PATH", envir));
	if (!ft_invalid_bin(binary, comm, vars))
	{
		comm->content = binary;
		_2denv = ft_2denv(envir);
		execve(binary, ft_2dcomm(comm), (char *const *)_2denv);
		perror(comm->content);
		vars->exit_status = errno;
	}
	else
		close(vars->old_fd);
	exit(vars->exit_status);
}

void	ft_builtin(t_list *comm, t_env **envir, t_vars *vars)
{
	if (comm && !ft_strncmp(comm->content, "cd\0", 5))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content, "echo\0", 7))
		ft_echo(comm, vars);
	else if (comm && !ft_strncmp(comm->content, "env\0", 7))
		ft_env(*envir, vars);
	else if (comm && !ft_strncmp(comm->content, "exit\0", 7))
		ft_exit(comm, vars);
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
		ft_export(*envir, vars, comm);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 7))
		ft_pwd(vars, envir);
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		ft_unset(comm, envir, vars);
}

int	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	int	fd;

	fd = -1;
	if (!node || !next_node)
	{
		printf("i should'nt get here\n");
		return (-1);
	}
	if (next_node->type == AMBIGUOUS)
	{
		ft_putstr_fd("minishell: ", 2);// fix for test (echo a | ls > /dev/stdin )
		ft_putstr_fd(next_node->content, 2);
		ft_putstr_fd(" ambiguous redirect\n", 2);
		vars->exit_status = 1;
		return (-1);
	}
	if (node->type != PIP && node->type != RED_IN)
		vars->pipe = 0;
	if (node->type == RED_OUT)
	{
		//if (access(next_node->content, W_OK) == -1 && vars->cmd_num)
		//{
		//	ft_putstr_fd("minishell: ", 2);// fix for test (echo a | ls > /dev/stdin )
		//	ft_putstr_fd(next_node->content, 2);
		//	//ft_putstr_fd(": Permission denied\n", 2);
		//	perror("");
		//	vars->exit_status = 1;
		//	return (-1);
		//}
		fd = open(next_node->content, O_CREAT | O_WRONLY | O_TRUNC, 0622);
		//printf("outfile: %s\n", next_node->content);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		vars->pfd[1] = fd;
	}
	if (node->type == RED_APPEND)
	{
		fd = open(next_node->content, O_WRONLY | O_CREAT | O_APPEND, 0622);
		//printf("file: %s\n", next_node->content);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		vars->pfd[1] = fd;
	}
	if (node->type == RED_IN)
	{
		fd = open(next_node->content, O_RDONLY);
		//printf("infile: %s\n", next_node->content);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		vars->old_fd = fd;
	}
	if (node->type == HEREDOC)
	{
		if (vars->heredoc_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status =  errno;
			return (-1);
		}
		vars->old_fd = vars->heredoc_fd;
		// close(vars->heredoc_fd);
		return (vars->heredoc_fd);
	}
	return (fd);
}

int	ft_isred(int t)
{
	if (t == RED_IN || t == RED_OUT || t == RED_APPEND || t == HEREDOC)
		return (1);
	return (0);
}
t_list	*ft_check4red(t_list *comm, t_vars *vars)
{
	t_list	*temp;
	t_list	*new_comm;

	temp = comm;
	new_comm = NULL;
	while (temp)
	{
		if (ft_isred(temp->type))
		{
			if (ft_handle_redir(temp, temp->next, vars) == -1)
				return (NULL);// need to free new comm at exit
			temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		else
		{
			ft_lstadd_back(&new_comm, ft_lstnew(temp->content, temp->type));
			temp = temp->next;
		}
	}
	return (new_comm);
}

void	ft_run(t_vars *vars, t_list *comm, t_env **envir)
{
	int		id;
	t_list	*new_comm;
	int		pid;

	new_comm = NULL;
	id = 0;
	while (comm)
	{
		vars->pfd[0] = vars->old_fd;
		vars->pfd[1] = 1;
		new_comm = ft_split_pipe(&comm, vars);
		if (vars->pipe)
			pipe(vars->pfd);
		comm = ft_check4red(comm, vars);
		if (comm)
		{
			if (!ft_is_builtin(comm->content))
			{
				id = fork();
				ft_catch(0, 0);
				if (id == -1)
				{
					perror("minishell: fork:");
					return ;
				}
				if (!id)
				{
					signal(SIGQUIT, SIG_DFL);
					ft_child(vars, comm, *envir);
				}
			}
			else
				ft_builtin(comm, envir, vars);
		}
		if (vars->old_fd)
			close(vars->old_fd);
		vars->old_fd = vars->pfd[0];
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		comm = new_comm;
		vars->cmd_num++;
		// dup_and_close(_stdout, 1);
	}
	if (waitpid(id, &pid, 0) > 0)
	{
    	if (WIFEXITED(pid))
        	vars->exit_status = WEXITSTATUS(pid);
		else if (WIFSIGNALED(pid))
        	vars->exit_status = 128 + WTERMSIG(pid);
		if (vars->exit_status == 131)
			printf("Quit: 3\n");
		ft_catch(0, -1);
	}
	while (wait(NULL) > 0)
    	;
}

void ft_execute(t_vars *vars, t_list *comm, t_env **envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	vars->pfd[1] = 1;
	vars->atoifail = 0;
	//printf("t:%d\n", comm->type);
	if (!comm)
		return ;
	//puts("before");
	
	// t_list *temp = comm;
	// while(temp)
	// {
	// 	printf("content: %s, type %d\n",temp->content, temp->type);
	// 	temp = temp->next;		
	// }
	//puts("after");
	comm = ft_dup_comm(comm);
	//temp = comm;
	//while(temp)
	//{
	//	printf("content: %s, type %d\n",temp->content, temp->type);
	//	temp = temp->next;		
	//}
	ft_run(vars, comm, envir);
}
