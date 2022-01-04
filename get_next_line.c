/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:19:40 by oairola           #+#    #+#             */
/*   Updated: 2022/01/04 12:18:13 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

int	ft_check_newl(char *str, int version)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (version == 1)
				return (1);
			else
				return (i);
		}
		i++;
	}
	if (version == 1)
		return (0);
	return (i);
}

int	reader(int fd, char **line, char **strsaver, char *str)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*temp;

	ret = BUFF_SIZE;
	if (!ft_check_newl(str, 1))
	{
		while (1)
		{
			ret = read(fd, buf, BUFF_SIZE);
			buf[ret] = '\0';
			temp = str;
			str = ft_strjoin(str, buf);
			free(temp);
			if (ret < BUFF_SIZE || ft_check_newl(buf, 1))
				break ;
		}
	}
	*line = ft_strsub(str, 0, ft_check_newl(str, 2));
	if (ft_check_newl(str, 1))
		strsaver[fd] = ft_strdup(ft_strchr(str, '\n') + 1);
	free(str);
	if (ret == 0 && *str == 0)
		return (0);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*strsaver[FD_MAX];
	char		*str;

	if (read(fd, strsaver[0], 0) < 0)
		return (-1);
	if (fd > FD_MAX || fd < 0 || !line || BUFF_SIZE == 0)
		return (-1);
	if (strsaver[fd])
	{
		str = ft_strdup(strsaver[fd]);
		ft_strdel(&(strsaver[fd]));
	}
	else
		str = ft_strnew(0);
	return (reader(fd, line, strsaver, str));
}
