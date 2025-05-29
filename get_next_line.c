/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neandrie <neandrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:09:44 by neandrie          #+#    #+#             */
/*   Updated: 2025/05/29 12:12:43 by neandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		s_len;
	char		*sub_s;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub_s = malloc(len + 1);
	if (!sub_s)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

char	*split_line(const char *s, char **after_nl)
{
	int		len_before_nl;
	char	*before_nl;

	if (!s)
		return (NULL);
	len_before_nl = 0;
	while (s[len_before_nl] && s[len_before_nl] != '\n')
		len_before_nl++;
	if (s[len_before_nl] == '\n')
		len_before_nl++;
	before_nl = ft_substr(s, 0, len_before_nl);
	if (!before_nl)
		return (NULL);
	if (s[len_before_nl - 1] == '\n')
		*after_nl = ft_strdup(s + len_before_nl);
	else
		*after_nl = NULL;
	return (before_nl);
}

static char	*return_and_shift_stash(char **stash)
{
	char	*before_nl;
	char	*after_nl;

	before_nl = split_line(*stash, &after_nl);
	if (!before_nl)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	free(*stash);
	*stash = after_nl;
	return (before_nl);
}

static int	read_and_append_until_nl(int fd, char **stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*new_stash;

	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (GNL_ERR);
		if (bytes_read == 0)
			return (GNL_EOF);
		buffer[bytes_read] = '\0';
		new_stash = ft_strjoin(*stash, buffer);
		if (!new_stash)
			return (GNL_ERR);
		free(*stash);
		*stash = new_stash;
	}
	return (GNL_OK);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			read_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	read_status = read_and_append_until_nl(fd, &stash);
	if (read_status == GNL_ERR || (*stash == '\0' && read_status == 0))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (return_and_shift_stash(&stash));
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
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	return (0);
}
