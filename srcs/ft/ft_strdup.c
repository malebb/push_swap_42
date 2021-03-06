/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:36:57 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/03 14:14:34 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strdup(const char *str)
{
	int		size_str;
	int		i;
	char	*dup;

	size_str = ft_strlen(str);
	dup = malloc(sizeof(char) * (size_str + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size_str)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
