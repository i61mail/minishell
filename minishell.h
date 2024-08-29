/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:11:35 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/29 08:48:20 by isrkik           ###   ########.fr       */
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
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_heredoc
{
	char	*value;
	char	*expand;
	char	*here_line;
	int		len;
	int		start;
	int		heredoc_fd;
}	t_heredoc;

typedef struct s_vars
{
	char	*read;
	int		catsh;
	int		befor_sing;
	int		exit_status;
	int		pfd[2];
	int		old_fd;
	int		pipe;
	int		numofpipes;
	int		bef_spac;
	int		len;
	int		start;
	int		heredoc_fd;
}	t_vars;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				catsh;
	struct s_env	*next;
}	t_env;

typedef struct s_list
{
	char			*content;
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
	QUOT,
	HEREDOC_DEL_Q,
	HEREDOC_DEL_U
}	t_token;

/*              utils  linked list       */

t_list		*ft_lstnew(void *content, int type);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstfree(t_list **comm);
void		free_all(char *read, t_list **comm, t_env **envir);

/*       is what  */

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			single_quo(t_vars *vars, int *i, char **str_temp);
int			ft_arequotes(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			ft_aresep(t_vars *vars, int *i, t_list **comm);
int			ft_isquotes(int c);
int			ft_isspace(int c);
int			ft_arespace(t_vars *vars, int *i);
int			ft_arealpha(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			ft_issep(int c);
int			quotes(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			count_dollar(char *str, int *i);
int			double_quo(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			dollar(t_vars *vars, int *i, char **str_temp, t_env **envir);
void		replace_expand(t_list *curr, char *str_temp, t_list **comm, int type);
int			expanding(t_vars *vars, int *i, char **str_temp, t_env **envir);
void		init_va(int *check, char **temp);
void		check_dollar(t_vars *vars, int *i, char **str_temp);
int			dollar_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			just_alpha(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			before_quotes(t_vars *vars, int *i, char **str_temp);
void		skip_digit(t_vars *vars, int *i, int *check);
int			ft_dollar(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			append_dollar2(t_vars *vars, int *i, char **temp, t_env **envir);
int			join_afterdollar(t_vars *vars, int *i, char **str_temp);
int			address_quote(t_vars *vars, int *i, char **str_temp, t_env **envir);
void		initi_vars(int *check, char **temp);
int			append_dollar(t_vars *vars, int *i, char **temp, t_env **envir);
int			ft_aresep3(t_vars *vars, int *i, int type, t_list **comm);
int			ft_aresep2(t_vars *vars, int *i, int type, t_list **comm);
int			process_heredoc(t_list *temp, t_vars *vars, t_env **envir);
int			heredoc_delimiter(t_vars *vars, int *i, t_list **comm);

/*        utils       */

int			ft_strlen(char *str);
char		*ft_substr(char *s, int start, int len);
char		*ft_strdup(char *s1);
char		*ft_strnjoin(char *s1, char *s2, size_t n);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strncpy(char *dst, char *src, int n);
char		**ft_split(char *s, char c);
void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_strcmp(char *s1, char *s2);
long long	ft_atoi(char *str);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strchr(const char *str, int c);
char		*ft_itoa(int nbr);

/*    utils check*/

int			even_odd(char *read);
int			ft_redircmp(char *s1, char *s2, int *i);
void		ft_error(t_list **comm);
int			ft_check_type(char *read, int *i, int *type);
int			ft_pipe(t_vars *vars, int *i, t_list **comm);
int			ft_append(t_vars *vars, int *i, t_list **comm);
int			ft_heredoc(t_vars *vars, int *i, t_list **comm);
int			ft_redirec(t_vars *vars, int *i, t_list **comm, char c);
int			ft_token(t_vars *vars, int i, t_list **comm, int type);
int			after_skip(char *str, int i, char c);

/*        env        */
int			strcpy_env(t_env **envir, char **env);
t_env		*ft_lstenv(char *key, char *value);
void		ft_lstenvadd_back(t_env **lst, t_env *new);
t_env		*ft_lstenvlast(t_env *lst);
void		ft_env_free(t_env **env);

/*       execution      */
void		ft_execute(t_vars *vars, t_list *comm, t_env *envir);

/*        builtins        */
int			ft_echo(t_list *command);
int			ft_cd(t_vars *vars, t_list *comm, t_env *envir);
int			ft_pwd(void);
int			ft_exit(int exit_status, int is_pipd);
int			ft_export(t_env *envir, t_list *command);
void		ft_env(t_env *envir);
void		ft_unset(t_list *command, t_env *envir);

/* 		  exec utils	*/
int			ft_env_length(t_env *envir);
int			ft_comm_length(t_list *comm);
int			ft_pipe_num(t_list *comm);
void		dup_and_close(int oldfd, int newfd);
char		*ft_locate_bin(char *command, char *path);
char		**ft_2denv(t_env *envir);
char		**ft_2dcomm(t_list *comm);
t_list		*ft_split_pipe(t_list **new_comm, t_vars *vars);
int 		ft_split_2(const char *str, const char *sep, char **k, char **v);

#endif