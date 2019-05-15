/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:43:05 by dysotoma          #+#    #+#             */
/*   Updated: 2018/10/22 15:43:08 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define LIM " \t\n\r\a"
#define TOKEN_BUF 64
#define INIT char *ret;char *tmp;int i = 0, j, k = 0, t = 0, check, c = 0
#define BINIT int len = 0

static int	bracket(char *str, int *j, int i, int c)
{
	BINIT;
	if (str[i + c] && str[i + c + 1] == '{')
	{
		while (str[i + c + 2 + len] != '}')
			if (str[i + c + 2 + len++] == '$')
			{
				ft_errprintf("msh: bad substitution\n");
				return (-1);
			}
		while (g_envp[*j] && SNCMP(g_envp[*j], str + i + 2, LEN(g_envp[*j]) -
		LEN(SCHR(g_envp[*j], '='))) != 0)
			(*j)++;
		if (str[i + c + 2 + len] != '}')
		{
			ft_errprintf("msh: no '}' to match '{' ");
			return (-1);
		}
		return (1);
	}
	else
		while (g_envp[*j] && SNCMP(g_envp[*j], str + i + 1, LEN(g_envp[*j]) -
		LEN(SCHR(g_envp[*j], '='))) != 0)
			(*j)++;
	return (0);
}

static char	*dollar(char *str)
{
	INIT;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * 2048)))
		return (NULL);
	str[i] == '~' ? i++ : 0;
	while (str[i + c])
	{
		while (str[i + c] && str[i + c] != '$')
			ret[t++] = str[i++];
		(!str[i + c + 1] || SCHR(LIM, str[i + c + 1])) && str[i + c] == '$' ?
		ret[t++] = str[i++] : i++;
		j = 0;
		if ((check = bracket(str, &j, i - 1, c)) == -1)
			return (NULL);
		k = -1;
		if (g_envp[j] && (tmp = SCHR(g_envp[j], '=') + 1))
			while (tmp[++k])
				ret[t++] = tmp[k];
		k = -1;
		while ((!g_envp[j] && str[i + c] && str[i + c] != '$') ||
		(str[i + c] && g_envp[j] && g_envp[j][++k] && g_envp[j][k] != '='))
			i++;
		check ? c += 2 : 0;
	}
	free(str);
	return (ret);
}

static char	*tilde(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if (!(ret = ft_strnew(2048)))
		return (NULL);
	while (ft_strncmp(g_envp[i], "HOME", 4) != 0)
		i++;
	if (g_envp[i])
	{
		ft_strcat(ret, SCHR(g_envp[i], '=') + 1);
		ft_strcat(ret, str + 1);
		free(str);
	}
	else
		ret = NULL;
	return (ret);
}

static int	expand(char ***str)
{
	char	*tmp;
	int		i;

	i = 0;
	if ((*str)[1])
	{
		while ((*str)[i])
		{
			if ((*str)[i][0] == '~')
				(*str)[i] = tilde((*str)[i]);
			if (ft_strchr((*str)[i], '$'))
			{
				if ((tmp = dollar((*str)[i])) == NULL)
					return (0);
				(*str)[i] = tmp;
			}
			i++;
		}
	}
	return (1);
}

char		**split_line(char *line)
{
	int		buf;
	int		position;
	char	**tokens;
	char	*token;

	position = 0;
	buf = TOKEN_BUF;
	if (!(tokens = (char**)ft_memalloc(sizeof(char*) * buf)))
		return (NULL);
	token = ft_strtok(line, LIM);
	while (token)
	{
		SNCMP(token, "", 1) != 0 ? tokens[position] = ft_strdup(token) : 0;
		SNCMP(token, "", 1) != 0 ? position++ : 0;
		if (position >= buf)
		{
			buf += TOKEN_BUF;
			if (!(tokens = (char**)ft_realloc(tokens, buf)))
				return (NULL);
		}
		token = ft_strtok(NULL, LIM);
	}
	tokens[position] = NULL;
	expand(&tokens) == 0 ? tokens = NULL : 0;
	return (tokens);
}
