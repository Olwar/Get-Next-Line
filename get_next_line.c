/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:19:40 by oairola           #+#    #+#             */
/*   Updated: 2021/12/20 15:04:10 by oairola          ###   ########.fr       */
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

int	check_newl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	reader(int fd, char **line, char *strsaver)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*str;
	int		i;
	int		a;

	a = 0;
	i = 0;
	str = NULL;
	if (strsaver)
		str = strsaver;
	if (!check_newl(str))
	{
		while(1)
		{
			ret = read(fd, buf, BUFF_SIZE);
			str = ft_strjoin(str, buf);
			if (ret <= 0 || check_newl(buf))
				break;
		}
	}
	while (str[i] != '\n' && str[i])
	{
		(*line)[i] = str[i];
		i++;
	}
	(*line)[i] = '\0';
	while (str[i])
		strsaver[a++] = str[i++];
	return (check_newl(str));
}

int get_next_line(const int fd, char **line)
{
	static char *strsaver[fd_max];

	if (fd > fd_max || fd < 0 || !line || !fd)
		return (-1);
	return (reader(fd, line, strsaver[fd]));
}