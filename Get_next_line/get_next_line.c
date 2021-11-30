/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:16:46 by asabbar           #+#    #+#             */
/*   Updated: 2021/11/26 21:24:50 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<stdio.h>
#include <fcntl.h>

char	*ft_read(char *rest, int fd)
{
	int		i;
	char	*s;

	s = malloc(BUFFER_SIZE + 1);
	if (!s)
		return (NULL);
	i = 1;
	while (i && !ft_strchr(rest, '\n'))
	{
		i = read (fd, s, BUFFER_SIZE);
		if (i == -1)
		{
			free(s);
			return (NULL);
		}
		s[i] = '\0';
		rest = ft_strjoin(rest, s);
	}
	free(s);
	return (rest);
}

char	*ft_line(char *rest)
{
	int		i;
	char	*line;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (rest[i] != '\n' && rest[i])
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_rest(char *rest)
{
	int		i;
	int		x;
	char	*newrest;
	int		lnrest;

	i = 0;
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	x = 0;
	lnrest = ft_strlen(&rest[i]);
	newrest = malloc(lnrest + 1);
	if (!newrest)
		return (NULL);
	while (rest[i])
		newrest[x++] = rest[i++];
	newrest[x] = '\0';
	free(rest);
	return (newrest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = ft_read(rest, fd);
	if (!rest)
		return (NULL);
	line = ft_line(rest);
	rest = get_next_rest(rest);
	return (line);
}
