/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:06:31 by dysotoma          #+#    #+#             */
/*   Updated: 2018/11/14 17:06:34 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define INIT int i = 0; char *tmps = NULL; char **tmp = NULL

static void	msh_setarg(char **tmp, char *tmps, int i)
{
	int used;

	used = 0;
	i = -1;
	while (g_envp[++i])
	{
		if (ft_cmptill(g_envp[i], tmps, '=') == 0)
		{
			tmp[i] = ft_strdup(tmps);
			used = 1;
		}
		else
			tmp[i] = ft_strdup(g_envp[i]);
	}
	if (!used)
		tmp[i] = ft_strdup(tmps);
	i = 0;
	while (g_envp[i])
		free(g_envp[i++]);
	free(g_envp);
	g_envp = tmp;
}

int			msh_setenv(char **ag)
{
	INIT;
	if ((ag[1] && ft_strchr(ag[1], '=')) || (ag[1] && ag[2]))
	{
		ag[2] ? ft_sprintf(tmps = ft_strnew(1024), "%s=%s", ag[1], ag[2]) : 0;
		!ag[2] ? tmps = ft_strdup(ag[1]) : 0;
		i = (int)ft_arrlen(g_envp);
		if (!(tmp = (char**)ft_memalloc(sizeof(char*) * (i + 2))))
			return (-1);
		msh_setarg(tmp, tmps, i);
		free(tmps);
		return (1);
	}
	ft_errprintf("msh: not enough or invalid argument: %s\nUsage: setenv \
[this=that/this] [NULL/that]\n", ag[1]);
	return (-1);
}

int			msh_unsetenv(char **args)
{
	int i;

	i = 0;
	if (args[1])
	{
		while (g_envp[i + 1])
		{
			while (ft_strncmp(g_envp[i], args[1], ft_strlen(args[1])) != 0
			&& g_envp[i + 1])
				i++;
			if (ft_strncmp(g_envp[i], args[1], ft_strlen(args[1])) == 0)
			{
				free(g_envp[i]);
				while (g_envp[i] && g_envp[i + 1])
				{
					g_envp[i] = g_envp[i + 1];
					i++;
				}
				g_envp[i] = NULL;
				return (1);
			}
		}
	}
	ft_errprintf("unsetenv: not enough arguments\n");
	return (-1);
}

int			msh_env(char **args)
{
	int i;

	i = 0;
	if (args[1] == NULL)
	{
		while (g_envp[i] && g_envp[i][0])
			ft_printf("%s\n", g_envp[i++]);
		return (1);
	}
	if (args[1])
		return (msh_setenv(args));
	return (1);
}
