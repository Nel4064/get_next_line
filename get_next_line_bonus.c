/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neandrie <neandrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:09:44 by neandrie          #+#    #+#             */
/*   Updated: 2025/06/02 16:25:11 by neandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	int		has_nl;
	char	*before_nl;

	if (!s)
		return (NULL);
	len_before_nl = 0;
	has_nl = 0;
	while (s[len_before_nl] && s[len_before_nl] != '\n')
		len_before_nl++;
	if (s[len_before_nl] == '\n')
	{
		len_before_nl++;
		has_nl = 1;
	}
	before_nl = ft_substr(s, 0, len_before_nl);
	if (!before_nl)
		return (NULL);
	if (has_nl)
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
	char	*buffer;
	ssize_t	bytes_read;
	char	*new_stash;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (GNL_ERR);
	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), GNL_ERR);
		if (bytes_read == 0)
			return (free(buffer), GNL_EOF);
		buffer[bytes_read] = '\0';
		new_stash = ft_strjoin(*stash, buffer);
		if (!new_stash)
			return (free(buffer), GNL_ERR);
		free(*stash);
		*stash = new_stash;
	}
	free(buffer);
	return (GNL_OK);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	int			read_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	read_status = read_and_append_until_nl(fd, &stash[fd]);
	if (read_status == GNL_ERR
		|| (read_status == GNL_EOF && *stash[fd] == '\0'))
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	return (return_and_shift_stash(&stash[fd]));
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		fd_blabla;
// 	int		fd_toto_1;
// 	int		fd_toto_2;
// 	char	*s_blabla;
// 	char	*s_toto_1;
// 	char	*s_toto_2;

// 	fd_blabla = open("blabla.txt", O_RDONLY);
// 	fd_toto_1 = open("toto_1.txt", O_RDONLY);
// 	fd_toto_2 = open("toto_2.txt", O_RDONLY);
// 	s_blabla = get_next_line(fd_blabla);
// 	s_toto_1 = get_next_line(fd_toto_1);
// 	s_toto_2 = get_next_line(fd_toto_2);
// 	while (s_blabla && s_toto_1 && s_toto_2)
// 	{
// 		printf("%s/n%s/n%s/n", s_blabla, s_toto_1, s_toto_2);
// 		free(s_blabla);
// 		free(s_toto_1);
// 		free(s_toto_2);
// 		s_blabla = get_next_line(fd_blabla);
// 		s_toto_1 = get_next_line(fd_toto_1);
// 		s_toto_2 = get_next_line(fd_toto_2);
// 	}
// 	close(fd_blabla);
// 	close(fd_toto_1);
// 	close(fd_toto_2);
// 	return (0);
// }
