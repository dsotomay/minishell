/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:02:44 by dysotoma          #+#    #+#             */
/*   Updated: 2018/09/24 15:03:01 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define INIT char *line = NULL;char **args;int status = 1;int i

char **g_envp;
t_minishell_func g_builtin[6];

static void	builtin_init(void)
{
	g_builtin[0] = &msh_echo;
	g_builtin[1] = &msh_cd;
	g_builtin[2] = &msh_setenv;
	g_builtin[3] = &msh_unsetenv;
	g_builtin[4] = &msh_env;
	g_builtin[5] = &msh_exit;
}

static void	new_env(char **be_coppied)
{
	int i;

	i = 0;
	while (be_coppied[i])
		i++;
	if (g_envp)
		free(g_envp);
	if (!(g_envp = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
		return ;
	i = -1;
	while (be_coppied[++i])
		g_envp[i] = ft_strdup(be_coppied[i]);
	g_envp[i] = NULL;
}

int			main(int ac, char **av, char **envp)
{
	INIT;
	(void)ac;
	(void)av;
	builtin_init();
	new_env(envp);
	while (status)
	{
		i = -1;
		ft_printf("hacker_man> ");
		get_next_line(0, &line);
		ft_strcmp(line, "") == 0 ? ft_strdel(&line) : 0;
		args = split_line(line);
		status = minishell_do(args);
		ft_memdel((void**)&line);
		if (args)
		{
			i = -1;
			while (args[++i])
				ft_strdel(&args[i]);
			free(args);
		}
	}
}
