/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:00:12 by dysotoma          #+#    #+#             */
/*   Updated: 2018/10/25 18:00:14 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*builtin_list(int i)
{
	static char *list[6];

	list[0] = "echo";
	list[1] = "cd";
	list[2] = "setenv";
	list[3] = "unsetenv";
	list[4] = "env";
	list[5] = "exit";
	return (list[i]);
}

int			msh_echo(char **arg)
{
	int i;
	int j;
	int newline;

	i = 0;
	if (arg[1])
		newline = ft_strcmp(arg[1], "-n") == 0 ? 0 : 1;
	else
		newline = 0;
	if (newline == 0)
		i++;
	while (arg[++i])
	{
		if (ft_strcmp(arg[i], ";") == 0)
			if (write(1, "\n", 1))
				return (1);
		j = -1;
		while (arg[i][++j])
			if (arg[i][j] != '"')
				ft_putchar(arg[i][j]);
		if (arg[i + 1])
			write(1, " ", 1);
	}
	newline == 1 ? write(1, "\n", 1) : 0;
	return (1);
}

static void	change_pwd(void)
{
	int		i;
	int		j;
	char	*buf;
	char	*tmp;
	char	*tmp2;

	buf = NULL;
	i = 0;
	j = 0;
	tmp = ft_strnew(1024);
	tmp2 = ft_strnew(1024);
	while (SNCMP(g_envp[i], "OLDPWD", 6) != 0)
		i++;
	while (SNCMP(g_envp[j], "PWD", 3) != 0)
		j++;
	ft_strcat(tmp, "OLDPWD");
	ft_strcat(tmp, SCHR(g_envp[j], '='));
	free(g_envp[j]);
	g_envp[j] = tmp;
	free(g_envp[i]);
	ft_strcat(tmp2, "PWD=");
	tmp = getcwd(buf, 0);
	ft_strcat(tmp2, tmp);
	free(tmp);
	g_envp[i] = tmp2;
}

int			msh_cd(char **args)
{
	struct stat	buf;
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	args[1] == NULL ? args[1] = ft_strdup("/nfs/2017/d/dysotoma") : 0;
	while (ft_strncmp(g_envp[i], "PWD", 3) != 0)
		i++;
	if (args[1] != NULL && SNCMP(args[1], "-", 1) == 0)
	{
		j = 0;
		while (ft_strncmp(g_envp[j], "OLDPWD", 6) != 0)
			j++;
		tmp = ft_strchr(g_envp[j], '=') + 1;
	}
	else
		tmp = args[1];
	if (args[1] == NULL)
		ft_errprintf("msh: no argument to \"cd\"\n");
	else if (stat(tmp, &buf) != 0)
		ft_errprintf("msh: no such file or directory: %s\n", tmp);
	!chdir(tmp) ? 0 : ft_errprintf("msh: permission denied: %s\n", tmp);
	change_pwd();
	return (1);
}

int			msh_exit(char **args)
{
	int i;

	i = 0;
	while (g_envp[i])
		free(g_envp[i++]);
	free(g_envp);
	if (args[0])
		exit(0);
	exit(0);
}
