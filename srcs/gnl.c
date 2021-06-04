/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:40:59 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/03 14:01:39 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	strncpy_from(char *dest, char *src, int n, int from)
{
	int		i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[from + i] = src[i];
		i++;
	}
	dest[from + i] = '\0';
}

static int	add_to_line(char **line, char buf[1001])
{
	int		size_line;
	char	*tmp;
	int		byte_to_add;
	int		line_read;

	size_line = ft_strlen(*line);
	byte_to_add = 0;
	while (buf[byte_to_add] != '\0' && buf[byte_to_add] != '\n')
		byte_to_add++;
	line_read = 0;
	if (buf[byte_to_add] == '\n')
		line_read = 1;
	tmp = ft_strdup(*line);
	if (!tmp)
		return (-1);
	free(*line);
	*line = malloc(sizeof(char) * (size_line + byte_to_add + 1));
	if (!(*line))
		return (-1);
	strncpy_from(*line, tmp, size_line, 0);
	free(tmp);
	strncpy_from(*line, buf, byte_to_add, size_line);
	ft_strcpy(buf, (buf + byte_to_add + line_read));
	return (line_read);
}

static int	finish_buf(char **line, char *buf)
{
	int		line_read;

	if (*buf)
	{
		line_read = add_to_line(line, buf);
		return (line_read);
	}
	return (0);
}

int	init_line(char **line)
{
	*line = malloc(sizeof(char) * (1));
	if (!(*line))
		return (-1);
	*line[0] = '\0';
	return (1);
}

int	gnl(char **line)
{
	static char		buf[1001] = {0};
	int				byte_read;
	int				line_read;

	if (init_line(line) == -1)
		return (-1);
	line_read = finish_buf(line, buf);
	if (line_read == -1)
		return (-1);
	if (line_read)
		return (1);
	byte_read = read(0, buf, 1000);
	while (byte_read)
	{
		if (byte_read == -1)
			return (-1);
		buf[byte_read] = '\0';
		line_read = add_to_line(line, buf);
		if (line_read == -1)
			return (-1);
		if (line_read)
			return (1);
		byte_read = read(0, buf, 1000);
	}
	return (0);
}
