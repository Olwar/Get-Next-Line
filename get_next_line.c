/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:41:20 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 15:10:42 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include "get_next_line.h"

/*
void input reader(fd, line)
{
	read from input
	write to output
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
*/

void	input_reader(fd)
{
	int	ret;
	char buf[BUF_SIZE + 1];

	while (ret = read(0, buf, BUF_SIZE))
		ft_putstr(buf);
}

int	read_function(int fd, char **line, char **strsaver)
{
	int	i;

	i = 0;
	while (*line[i] != '\n' && *line[i])
	{
		if (strsaver[i] != line[i])
			strsaver[i++] = line[i];
		i++;
	}
	if (*line[i] == '\n')
		return (1);
	else
		return (0);
}

int get_next_line(const int fd, char **line)
{
	static char *strsaver[fd];
	int flag;
	
	if (fd == 1)
	{
		input_reader(fd);
		return (0);
	while (1)
	{
		strsaver = (static char *)malloc
		flag = read_function(fd, line, &strsaver);
	}
	return (flag);
}