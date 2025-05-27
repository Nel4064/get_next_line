/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neandrie <neandrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:09:44 by neandrie          #+#    #+#             */
/*   Updated: 2025/05/27 18:13:43 by neandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*strstat;
	char		*tmp;
	char		buffer[BUFFER_SIZE];
	ssize_t		bytes_read;
	int			i;

	if (!strstat)
		strstat = malloc(sizeof(unsigned long));
	i = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		
	}
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*s;

	fd = open("blabla.txt", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		get_next_line(fd);
	}
	close(fd);
	return (0);
}
