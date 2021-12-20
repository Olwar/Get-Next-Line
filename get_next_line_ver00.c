/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:41:20 by oairola           #+#    #+#             */
/*   Updated: 2021/12/20 14:18:07 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

int		ft_newl_1check_2len(char *str, int version)
{
	int	i;

	i = 0;
	if (version == 1)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
	if (version == 2)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
		return (i);
	}
	return (0);
}

char	*ft_strjoin_newl(char const *s1, char const *s2)
{
	int		i;
	int		a;
	char	*str;

	a = ft_newl_1check_2len((char *)s2, 2);
	i = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (i + a) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
/*	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}*/
	a = 0;
	while (s2[a] != '\n' && s2[a])
	{
		str[i] = s2[a];
		i++;
		a++;
	}
	str[i] = '\0';
	return (str);
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
	int		ret;
	char	buf[BUFF_SIZE + 1];
	int		a;
	char	*str;
	int		i;

	i = 0;
	str = strdup(strsaver[fd]);
	if (!ft_newl_1check_2len(str, 1))
	{
		ft_strdel(str);
		while (!ft_newl_1check_2len(str, 1))
		{
			ret = read(fd, buf, BUFF_SIZE);
			if (ret <= 0)
			{	
				free(str);
				return (0);
			}
			str = ft_strjoin_newl(str, buf);
		}
	}
	*line = ft_strjoin_newl(*line, str);
	while (str[i - 1] != '\n' && str[i])
		i++;
	a = 0;
	while (str[i])
		strsaver[fd][a++] = str[i++];
	while (strsaver[fd][a])
		strsaver[fd][a++] = '\0';
	return (ft_newl_1check_2len(str, 1));
}

int get_next_line(const int fd, char **line)
{
	static char *strsaver[fd_max];

	if (fd > fd_max || fd < 0 || !line || !fd)
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
