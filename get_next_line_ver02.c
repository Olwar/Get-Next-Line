/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:19:40 by oairola           #+#    #+#             */
/*   Updated: 2022/01/03 15:39:59 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

char	*ft_strjoin_eof(char *s1, char *s2, int ret)
{
	int		i;
	int		a;
	char	*str;

	a = ret;
	i = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (i + a) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	a = 0;
	while (a != ret && s2[a])
	{
		str[i] = s2[a];
		i++;
		a++;
	}
	str[i] = '\0';
	return (str);
}

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

int	reader(int fd, char **line, char **strsaver)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*str;
	int		i;
	int		a;
	char	*temp;

	temp = NULL;
	str = NULL;
	a = 0;
	i = 0;
	ret = BUFF_SIZE;
	if (strsaver[fd] && ft_strcmp("", strsaver[fd]) != 0)
	{
		str = ft_strdup(strsaver[fd]);
		ft_strdel(&(strsaver[fd]));
	}
	else
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret <= 0)
			return (ret);
		buf[ret] = '\0';
		if (ret < BUFF_SIZE)
			str = ft_strndup(buf, ret); //memory leak
		else
			str = ft_strdup(buf); //memory leak
	}
	if (!ft_check_newl(str, 1))
	{
		while (1)
		{
			ret = read(fd, buf, BUFF_SIZE);
			buf[ret] = '\0';
			if (ret < BUFF_SIZE)
			{
				temp = str;
				str = ft_strjoin_eof(str, buf, ret); //loses malloc from line 90 / 92
				free(temp);
			}
			else
			{
				temp = str;
				str = ft_strjoin(str, buf); //loses malloc from line 90 / 92
				free(temp);
			}
			if (ret < BUFF_SIZE || ft_check_newl(buf, 1))
			{
				ft_bzero(buf, BUFF_SIZE + 1);
				break ;
			}
		}
	}
	//free(temp);
	*line = ft_strsub(str, 0, ft_check_newl(str, 2)); // not a memory leak ?
	if (ft_check_newl(str, 1))
	{
		strsaver[fd] = ft_strdup(ft_strchr(str, '\n') + 1); //how can i not make these the same address - if i free str, //also strsaver gets deleted
		//strsaver[fd]++;
	}
	//else
	//	ft_strclr(strsaver[fd]);
	// need to free mallocs from line 100 / 102
	free(str);
	if (ret == 0)
		return (0);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*strsaver[FD_MAX];

	if (read(fd, strsaver[0], 0) < 0)
		return (-1);
	if (fd > FD_MAX || fd < 0 || !line || !fd || BUFF_SIZE == 0)
		return (-1);
	return (reader(fd, line, strsaver));
}
