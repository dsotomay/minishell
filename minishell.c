/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:16:36 by dysotoma          #+#    #+#             */
/*   Updated: 2018/10/24 14:16:42 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ms_access(char *str)
{
	char	**new;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	new = NULL;
	while (g_envp[i] && ft_strncmp(g_envp[i], "PATH", 4) != 0)
		i++;
	if (g_envp[i] && ft_strncmp(g_envp[i], "PATH", 4) == 0)
		new = ft_strsplit(ft_strchr(g_envp[i], '=') + 1, ':');
	i = -1;
	while (new && new[++i])
	{
		tmp = ft_strjoin(new[i], "/");
		tmp2 = ft_strjoin(tmp, str);
		if (access(tmp2, X_OK) == 0)
		{
			ft_strdel(&tmp);
			return (tmp2);
		}
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (ft_strdup(str));
}

static int	minishell_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*arg;

	pid = fork();
	if (pid == 0)
	{
		arg = ms_access(args[0]);
		if (execve(arg, args, g_envp) == -1)
		{
			if (access(arg, F_OK) == 0 && access(arg, X_OK) != 0)
				ft_errprintf("msh: permission denied: %s\n", args[0]);
			else
				ft_errprintf("msh: command not found: %s\n", args[0]);
		}
		exit(-1);
	}
	else if (pid < 0)
		ft_errprintf("msh: unable to fork\n");
	wpid = waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(pid, &status, WUNTRACED);
	return (1);
}

int			minishell_do(char **args)
{
	int i;

	if (args[0] == NULL)
		return (1);
	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(args[0], builtin_list(i)) == 0)
			return (g_builtin[i](args));
		i++;
	}
	return (minishell_launch(args));
}
