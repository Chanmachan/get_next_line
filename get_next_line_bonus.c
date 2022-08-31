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

#include "get_next_line_bonus.h"

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

	rd_bytes = 1;
	buf = (char *) malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (rd_bytes != 0 && !ft_strchr(str, '\n'))
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
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
		i++;
	if (str[i] == '\n')
		i++;
	rtn_str = ft_substr(str, 0, i);
	if (rtn_str == NULL)
		return (NULL);
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
	new_str = ft_substr(&str[i], 0, ft_strlen(&str[i]));
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*rtn_str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str[fd] = read_lines(str[fd], fd);
	if (!str[fd])
		return (NULL);
	rtn_str = get_one_line(str[fd]);
	str[fd] = delete_last_line(str[fd]);
	return (rtn_str);
}

/*#include <fcntl.h>//open
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
//	int		fd2;
//	int		fd3;
	fd1 = open("test/text00.txt", O_RDONLY);
//	fd2 = open("test/text00.txt", O_RDONLY);
//	fd3 = open("test/41_with_nl.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
//		line = get_next_line(fd2);
//		printf("line [%02d]: %s", i, line);
//		free(line);
//		line = get_next_line(fd3);
//		printf("line [%02d]: %s", i, line);
//		free(line);
		i++;
	}
	close(fd1);
//	close(fd2);
//	close(fd3);
	system("leaks -q a.out");
	return (0);
 }*/

/*int main(void)
{
	char 	*str;
	int 	fd[5];
	size_t 	i;

	i = 0;
	fd[1] = open("test/41_no_nl.txt", O_RDONLY);
	fd[0] = open("test/text00.txt", O_RDONLY);
	printf("fd : %d\n", fd[1]);
	while (1)
	{
		str = get_next_line(fd[0]);
//		printf("[%zu] : %s\n-------------\n", i, str);
		printf("%s", str);
		if (str == NULL)
			break;
		free(str);
		i++;
	}
	while (1)
	{
		str = get_next_line(fd[1]);
//		printf("[%zu] : %s\n-------------\n", i, str);
		printf("%s", str);
		if (str == NULL) {
			break;
		}
		free(str);
		i++;
	}
	while (1)
	{
		str = get_next_line(fd[2]);
//		printf("[%zu] : %s\n-------------\n", i, str);
		printf("%s", str);
		if (str == NULL) {
			break;
		}
		free(str);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
//	system("leaks a.out");
}*/
//-fsanitize=address -g