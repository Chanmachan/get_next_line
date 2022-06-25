//
// Created by 本間優之介 on 2022/06/20.
//
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	if (n == 0)
	{
		return (len_src);
	}
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len_src);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
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

	if (s1 == NULL)
	{
		s1 = (char *) malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	len_rtn_str = ft_strlen(s1) + ft_strlen(s2);
	rtn_str = (char *) malloc (sizeof(char) * (len_rtn_str + 1));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(rtn_str, s2, len_rtn_str + 1);;
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
