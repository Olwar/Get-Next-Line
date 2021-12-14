/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:41:20 by oairola           #+#    #+#             */
/*   Updated: 2021/12/14 15:09:19 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

/*
void input reader(fd, line)
{
	read from input
	write to output
}

char *read function(int fd, char **line, pointer to static char)
{
		read(fd, buf, buf_size);
		strjoin(line, buf);
		strjoin(strsaver[fd], buf);
		return (line);
}

int read function(int fd, char **line, pointer to static char)
{
	while line[i] = \n or EOF
		go through char by char
		start writing when line[i] is not static char anymore!!
		also save into static char to where to start next line reading
		if \n
			flag = 0
		if EOF
			flag = -1
	return flag
}

get next line(fd, line)
{
	if fd 1
		input reader
	int = read function : read one line and save to line variable without the \n
		return -1 if couldnt read
	return 1 if still stuff left, 0 if end of file, -1 if couldnt read
}

int		ft_endres(fd)
{
	char	*str;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	int		i;

	i = 0;
	while (ret = read(fd, buf, BUFF_SIZE))
	{
		if (buf[ret] == '\n')
			return (1);
		i++;
	}
	return (0);
}

*/

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

	while ((ret = read(fd, buf, BUFF_SIZE)) && (!ft_newl_1check_2len(strsaver[fd], 1)))
	{
		strsaver[fd] = ft_strdup(buf);
		*line = ft_strjoin(*line, strsaver[fd]);
		if (!line)
			return (-1);
	}
	return (ft_newl_1check_2len(strsaver[fd], 1));
}

int get_next_line(const int fd, char **line)
{
	static char *strsaver[fd_max];

	if (fd > fd_max || fd <= 0 || !line)
		return (-1);
	if (fd == 1)
	{
		input_reader();
		return (0);
	}
	if (!strsaver[fd]) 
		strsaver[fd] = ft_strnew(BUFF_SIZE + 1);
	return (read_function(fd, line, strsaver));
}