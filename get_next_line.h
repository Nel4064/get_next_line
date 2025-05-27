/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neandrie <neandrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:09:53 by neandrie          #+#    #+#             */
/*   Updated: 2025/05/27 17:57:37 by neandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> // for read(), close(), ssize_t
# include <stdlib.h> // for malloc(), free()
# include <fcntl.h> // for open()
# include <stddef.h> // for size_t

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strcpy(char *dest, const char *src)
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);

#endif