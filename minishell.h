/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:49:14 by dysotoma          #+#    #+#             */
/*   Updated: 2018/09/24 14:49:27 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define LEN(x) ft_strlen(x)
# define SCHR(x,y) ft_strchr(x,y)
# define SNCMP(x,y,z) ft_strncmp(x,y,z)

# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft/libft.h"

typedef int	(*t_minishell_func)(char **args);

extern	char **g_envp;
extern	t_minishell_func g_builtin[6];

int		minishell_do(char **args);
char	**split_line(char *line);
char	*builtin_list(int i);

int		msh_echo(char **arg);
int		msh_cd(char **args);
int		msh_setenv(char **args);
int		msh_unsetenv(char **args);
int		msh_env(char **args);
int		msh_exit(char **args);

#endif
