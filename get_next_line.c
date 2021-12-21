/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:19:40 by oairola           #+#    #+#             */
/*   Updated: 2021/12/20 15:57:27 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

/*
mene kirjain kerrallaan
kirjoita lineen '\n' asti
seivaa '\n' jalkeiset strsaveriin
-uusi tiedosto-
kirjoita '\n' jalkeiset '\n':aan tai tiedoston loppuun asti

reader
	kirjain kerrallaan niin kauan kunnes buffissa on '\n'
*/

char	*ft_strjoin_eof(char const *s1, char const *s2, int ret)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		a;
	char	*str;

	a = ft_strlen(s2);
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
	while (s2[a] != '\0' && s2[a])
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
	return (0);
}

int	reader(int fd, char **line, char **strsaver)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*str;
	int		i;
	int		a;

	a = 0;
	i = 0;
	if (strsaver[fd])
	{
		str = ft_strdup(strsaver[fd]);
		ft_strclr(strsaver[fd]);
	}
	else
	{
		read(fd, buf, BUFF_SIZE);
		str = ft_strdup(buf);
	}
	if (!ft_check_newl(str, 1))
	{
		while(1)
		{
			ret = read(fd, buf, BUFF_SIZE);
			if (ret < BUFF_SIZE)
				str = ft_strjoin_eof(str, buf, ret);
			else
				str = ft_strjoin(str, buf);
			if (ret <= 0 || ft_check_newl(buf, 1))
			{
				ft_bzero(buf, BUFF_SIZE + 1);
				break;
			}
		}
	}
	*line = ft_strsub(str, 0, ft_check_newl(str, 2));
	if (ft_check_newl(str, 1))
	{
		strsaver[fd] = ft_strchr(str, '\n');
		strsaver[fd]++;
	}
	else
		ft_strclr(strsaver[fd]);
	return (ft_check_newl(str, 1));
}

int get_next_line(const int fd, char **line)
{
	static char *strsaver[fd_max];

	if (fd > fd_max || fd < 0 || !line || !fd)
		return (-1);
	*line = NULL;
	return (reader(fd, line, strsaver));
}