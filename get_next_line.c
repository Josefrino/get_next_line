/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josvieir <josvieir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:48:43 by josvieir          #+#    #+#             */
/*   Updated: 2024/02/17 20:01:40 by josvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*continue_reading(int fd, char **temp)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		*temp = ft_strjoin(*temp, buffer);
		if (has_new_line(*temp))
			break ;
	}
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (extract_line(temp));
}

char	*get_next_line(int fd)
{
	static char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	if (has_new_line(temp))
		return (extract_line(&temp));
	return (continue_reading(fd, &temp));
}

/*int main(void)
{
	int fd = open("fd", O_RDONLY);
	char	*str;
	int		i = 0;

	while (i < 10)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	return (0);
}*/