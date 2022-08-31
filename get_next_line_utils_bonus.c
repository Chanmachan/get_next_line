/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:09:05 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/07/12 03:09:06 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

//add str == NULL

static size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	if (n == 0)
		return (len_src);
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len_src);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	if (size == 0)
		return (0);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (size < len_dst)
		return (size + len_src);
	if (size > len_dst)
	{
		while (dst[i] != '\0')
			i++;
		dst = dst + i;
		i = 0;
		while (i < size - len_dst - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_dst + len_src);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*rtn_str;
	size_t	len_rtn_str;

	len_rtn_str = ft_strlen(s1) + ft_strlen(s2);
	rtn_str = (char *) malloc (sizeof(char) * (len_rtn_str + 1));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(rtn_str, s2, len_rtn_str + 1);
	free(s1);
	return (rtn_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn_str;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_substr("", 0, 1));
	if (len > len_s - start)
		len = len_s - start;
	rtn_str = (char *) malloc (sizeof(char) * (len + 1));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, &s[start], len + 1);
	return (rtn_str);
}

//if (s1 == NULL) added to solve the segfault

/*#include <string.h>
#include <stdio.h>
int main(void)
{
	char a[] = "";
	char b[] = "42";
	char *a_b;

	a_b = ft_strjoin(a, b);
	printf("%s\n", a_b);
}*/
