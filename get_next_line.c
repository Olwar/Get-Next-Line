/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:41:20 by oairola           #+#    #+#             */
/*   Updated: 2021/12/14 16:14:57 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		ft_newl_1check_2len(char *str, int version)
{
	int	i;

	i = 0;
	if (version == 1)
		while (str[i])
			if (str[i] == '\n')
				return (1);
		return (0);
	if (version == 2)
		while (str[i])
			if (str[i] == '\n')
				return (i);
		return (i);
}

void	input_reader()
{
	int	ret;
	char buf[BUFF_SIZE + 1];

	while ((ret = read(0, buf, BUFF_SIZE)))
		ft_putstr(buf);
}

int		read_function(int fd, char **line, char **strsaver)
{
	int	ret;
	char buf[BUFF_SIZE + 1];
	char *temp;

	while ((ret = read(fd, buf, BUFF_SIZE)) && (!ft_newl_1check_2len(strsaver[fd], 1)))
	{
		strsaver[fd] = ft_strdup(buf);
		*line = ft_strjoin(*line, strsaver[fd]);
		if (!line)
		{
			free (line);
			return (-1);
		}
	}
	return (ft_newl_1check_2len(strsaver[fd], 1));
}

int get_next_line(const int fd, char **line)
{
	static char *strsaver[fd_max];

	if (fd > fd_max || fd <= 0 || !line)
		return (-1);
	if (fd == 0)
	{
		input_reader();
		return (0);
	}
	if (!strsaver[fd]) 
		strsaver[fd] = ft_strnew(BUFF_SIZE + 1);
	return (read_function(fd, line, strsaver));
}