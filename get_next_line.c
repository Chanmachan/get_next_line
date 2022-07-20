/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:09:09 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/07/12 03:09:10 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *s, int c)
{
	char	*new_s;
	size_t	i;

	new_s = (char *) s;
	i = 0;
	if (!s)
		return (NULL);
	while (new_s[i] != '\0')
	{
		if (new_s[i] == (char) c)
			return (new_s + i);
		i++;
	}
	if ((char) c == '\0')
		return (new_s + i);
	return (NULL);
}

char	*read_lines(char *str, int fd)
{
	char		*buf;
	ssize_t		rd_bytes;
	char		*tmp;

	rd_bytes = 1;
	while (rd_bytes != 0 && !ft_strchr(str, '\n'))
	{
		buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (NULL);
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		free(buf);
	}
	return (str);
}

char	*get_one_line(char *str)
{
	size_t	i;
	char	*rtn_str;

	if (str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == '\n')
		i++;
	rtn_str = ft_substr(str, 0, i);
	if (rtn_str == NULL)
	{
		free(str);
		return (NULL);
	}
	return (rtn_str);
}

//str[0] == '\0' if empty

char	*delete_last_line(char *str)
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '\n')
		i++;
	new_str = ft_substr(&str[i], 0, ft_strlen(str + i));
	if (new_str == NULL)
		return (NULL);
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*rtn_str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = read_lines(str, fd);
	if (!str)
		return (NULL);
	rtn_str = get_one_line(str);
	str = delete_last_line(str);
	return (rtn_str);
}

/*#include <fcntl.h>//open
#include <stdio.h>

int main(void)
{
	char 	*str;
	int 	fd;
	size_t 	i;

	i = 0;
	fd = open("test/test.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
//		printf("[%zu] : %s\n-------------\n", i, str);
		printf("%s", str);
		if (str == NULL)
			break;
		free(str);
		i++;
	}
	close(fd);
//	system("leaks a.out");
}*/
//-fsanitize=address -g