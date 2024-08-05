/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:11:35 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/05 15:44:16 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_vars
{
	char	*read;
	int		catsh;
	char	*curr;
	int		befor_sing;
}	t_vars;

typedef struct s_list
{
	void			*content;
	int				type;
	struct s_list	*next;
}	t_list;

typedef enum s_token
{
	COMM,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	PIP,
	QUOT
}	t_token;

/*              utils  linked list       */

t_list	*ft_lstnew(void *content, int type);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

/*             utils  main         */

int		ft_strlen(char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
int		ft_isspace(int c);
int		ft_issep(int c);
void	ft_lstfree(t_list **comm);
int		ft_isquotes(int c);
int		ft_isdouble(char *read, int *i);
int		ft_issingle(char *read, int *i);
int		even_odd(char *read);
int		ft_redircmp(char *s1, char *s2, int *i);
void	ft_error(t_list **comm);
int		ft_check_type(char *read, int *i, int *type);
int		ft_pipe(t_vars *vars, int *i, t_list **comm);
int		ft_append(t_vars *vars, int *i, t_list **comm);
int		ft_heredoc(t_vars *vars, int *i, t_list **comm);
int		ft_redirec(t_vars *vars, int *i, char c, t_list **comm);
int		ft_aresep(t_vars *vars, int *i, t_list **comm);
int		ft_arespace(char *read, int *i);
int		ft_arealpha(t_vars *vars, int *i, t_list **comm);
int		ft_token(t_vars *vars, int i, t_list **comm, int type);
int		skip_space(char *str, char c, int red);
int		after_skip(char *str, int i, int red);
int		ft_arequotes(t_vars *vars, int *i, t_list **comm);
char	*ft_strnjoin(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memset(void *b, int c, size_t len);

#endif