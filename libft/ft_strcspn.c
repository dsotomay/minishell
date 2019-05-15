/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:36:48 by dysotoma          #+#    #+#             */
/*   Updated: 2018/09/25 15:36:50 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s1, const char *s2)
{
	size_t	ret;

	ret = 0;
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
			return (ret);
		ret++;
		s1++;
	}
	return (ret);
}
