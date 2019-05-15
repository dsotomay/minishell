/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmptill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:28:29 by dysotoma          #+#    #+#             */
/*   Updated: 2018/11/01 19:28:31 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cmptill(const char *str1, const char *str2, int c)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && (str1[i] != c || str2[i] != c))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
