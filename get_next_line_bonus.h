/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neandrie <neandrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:09:53 by neandrie          #+#    #+#             */
/*   Updated: 2025/06/02 16:28:22 by neandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h> // for read(), close(), ssize_t
# include <stdlib.h> // for malloc(), free()
# include <fcntl.h> // for open()
# include <stddef.h> // for size_t
# include <limits.h> // for OPEN_MAX

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# define GNL_OK 1
# define GNL_EOF 0
# define GNL_ERR -1

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*split_line(const char *str, char **after_nl);

#endif