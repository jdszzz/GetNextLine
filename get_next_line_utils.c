/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelmon <albelmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:36:16 by albelmon          #+#    #+#             */
/*   Updated: 2026/01/05 16:23:04 by albelmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size == 0)
		return (j);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}

char	*ft_strdup(const char *s)
{
	char			*cpy;
	size_t			i;
	size_t			len_s;

	i = -1;
	len_s = ft_strlen(s);
	cpy = malloc(len_s + 1);
	if (!cpy)
		return (NULL);
	while (++i < len_s)
		cpy[i] = s[i];
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	char	*s3;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = malloc(len_s1 + len_s2 + 1);
	if (!s3)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		s3[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		s3[len_s1 + i] = s2[i];
	s3[len_s1 + len_s2] = '\0';
	free(s1);
	return (s3);
}
