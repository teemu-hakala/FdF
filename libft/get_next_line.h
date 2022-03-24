/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:23:04 by thakala           #+#    #+#             */
/*   Updated: 2022/03/24 14:03:11 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 2797
# define FD_MAX 10240
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int	get_next_line(const int fd, char **line);

#endif
