/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:34:47 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 09:41:30 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i])
		i++;
	return (i);
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
	while (s2[a] != '\0' && s2[i])
	{
		str[i] = s2[a];
		i++;
		a++;
	}
	str[i] = '\0';
	return (str);
}

int main()
{
	char *s1;
	char *s2 = "bumba";

	s1 = NULL;
	s1 = ft_strjoin(s1, s2);
	printf("%s\n", s1);
}